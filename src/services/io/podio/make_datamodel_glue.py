#!/usr/bin/env python
#
# Copyright 2022, David Lawrence
# Subject to the terms in the LICENSE file found in the top-level directory.
#
#

#
#  This is a stop gap and not intended for long term.  2022-07-09  DL
#
# This will scan the list of files in the EDM4hep datamodel directory
# (pointed to by the EDM4HEP_ROOT environment variable). Using the
# filenames, it will generate some C++ code that can be used by
# the JEventSourcePODIO and EDM4hepWriter classes to read and write all
# of those types.

import os
import sys
import glob

print('Generating datamodel_glue.h ...')

EDM4HEP_ROOT = os.environ.get("EDM4HEP_ROOT")

# poor man's command line parsing
for arg in sys.argv:
    if arg.startswith('EDM4HEP_ROOT'):
        if '=' in EDM4HEP_ROOT: EDM4HEP_ROOT = arg.split('=')[1]


# Check if EDM4HEP_ROOT is set
if not EDM4HEP_ROOT:
    print("ERROR: EDM4HEP_ROOT env. variable is None or empty and no EDM4HEP=/path/to/edm4hep on command line!\n"
          "       Please point EDM4HEP_ROOT to edm4hep installation root.\n"
          "       This script looks for '{EDM4HEP_ROOT}/include/edm4hep/*Collection.h'\n")
    sys.exit(1)


collectionfiles = glob.glob(EDM4HEP_ROOT+'/include/edm4hep/*Collection.h')
header_lines  = []
copy_lines    = []
make_lines    = []
put_lines     = []
for f in collectionfiles:
    header_fname = f.split('/edm4hep')[-1]
    basename = header_fname.split('/')[-1].split('Collection.h')[0]

    header = '#include <edm4hep' + header_fname + '>'
    header_lines.append(header)

    make_lines.append('    if( className == "vector<edm4hep::'+basename+'Data>"){ return new EICEventStore::DataVectorT<edm4hep::'+basename+'Data>(name, className, collectionID); }')

    copy_lines.append( '    if( dv->className == "vector<edm4hep::'+basename+'Data>") {' )
    copy_lines.append( '        auto *dvt = reinterpret_cast<EICEventStore::DataVectorT<edm4hep::'+basename+'Data>*>( dv );' )
    copy_lines.append( '        return CopyToJEventT<edm4hep::'+basename+', edm4hep::'+basename+'Obj, edm4hep::'+basename+'Data>(dvt, event, podio_objs);' )
    copy_lines.append( '    }')

    put_lines.append('    if( ! fac->GetAs<edm4hep::'+basename+'>().empty() )')
    put_lines.append('       {return PutPODIODataT<edm4hep::'+basename+', edm4hep::'+basename+'Collection>( writer, fac, store );}')

make_lines.append('    if( className == "vector<podio::ObjectID>"){ return new EICEventStore::DataVectorT<podio::ObjectID>(name, className); }')
make_lines.append('    std::cerr << "Unknown classname: " << className << " for branch " << name << std::endl;')
make_lines.append('    return nullptr;')
copy_lines.append('    std::cerr << "Unknown classname: " << dv->className << std::endl;')
put_lines.append('    return "";')

with open('datamodel_includes.h', 'w') as f:
    f.write('\n// This file automatically generated by the make_datamodel.py script\n\n')
    f.write('\n'.join(header_lines))
    f.write('\n')
    f.close()

with open('datamodel_glue.h', 'w') as f:
    f.write('\n// This file automatically generated by the make_datamodel.py script\n')
    f.write('#include <JANA/JEvent.h>\n')
    f.write('#include <JANA/JFactory.h>\n')
    f.write('#include <podio/CollectionIDTable.h>\n')
    f.write('#include <EICEventStore.h>\n')
    f.write('#include <EDM4hepWriter.h>\n')
    f.write('#include <datamodel_includes.h>\n')
    f.write('\n')
    f.write('\ntemplate <typename T, typename Tobj, typename Tdata> void CopyToJEventT(EICEventStore::DataVectorT<Tdata> *dvt, std::shared_ptr <JEvent> &jevent, std::vector<podio::ObjBase*> &podio_objs);')
    f.write('\ntemplate <class T, class C> std::string PutPODIODataT( EDM4hepWriter *writer, JFactory *fac, EICEventStore &store );\n')

    f.write('\nstatic EICEventStore::DataVector* MakeDataVector(const std::string &name, const std::string &className, int collectionID=-1){\n')
    f.write('\n'.join(make_lines))
    f.write('\n}\n')

    f.write('\n')
    f.write('\nstatic void CopyToJEvent(EICEventStore::DataVector *dv, std::shared_ptr<JEvent> &event, std::vector<podio::ObjBase*> &podio_objs){\n')
    f.write('\n'.join(copy_lines))
    f.write('\n}\n')

    f.write('\n// Test data type held in given factory against being any of the known edm4hep data types.')
    f.write('\n// Call PutPODIODataT if match is found. (Factory must have called EnableAs for edm4hep type.)')
    f.write('\nstatic std::string PutPODIOData(EDM4hepWriter *writer, JFactory *fac, EICEventStore &store){\n')
    f.write('\n'.join(put_lines))
    f.write('\n}\n')
    f.close()
