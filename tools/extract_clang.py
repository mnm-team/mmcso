#!/usr/bin/env python

# requires libclang python package (pip install clang)
import subprocess
command = "pip show clang | grep Location: | awk '{ print $2 }'"
result = subprocess.run(command, shell=True, capture_output=True, text=True)

print('libclang found in: ' + result.stdout.strip())
clang_py_module = result.stdout.strip()

import argparse

import re
import os, sys
sys.path.append(clang_py_module)

import clang
from clang.cindex import Index, CursorKind

clang.cindex.Config.set_library_file(os.path.join(clang_py_module, 'clang/native/libclang.so'))


# Thread-safe functions (see MPI 4.1, Section 11.6 and Table 11.1)
#
# Quote:
# "Regardless of whether or not the MPI implementation is thread compliant, a subset of MPI
#  functions must always be thread safe. A complete list of such MPI functions is given in
#  Table 11.1."
#
# Table 11.1:
# ---------------------------------
# MPI_INITIALIZED
# MPI_FINALIZED
# MPI_GET_VERSION
# MPI_GET_LIBRARY_VERSION
# MPI_INFO_CREATE
# MPI_INFO_CREATE_ENV
# MPI_INFO_SET
# MPI_INFO_DELETE
# MPI_INFO_GET_STRING
# MPI_INFO_GET_NKEYS
# MPI_INFO_GET_NTHKEY
# MPI_INFO_DUP
# MPI_INFO_FREE
# MPI_INFO_F2C
# MPI_INFO_C2F
# MPI_SESSION_CREATE_ERRHANDLER
# MPI_SESSION_CALL_ERRHANDLER
# MPI_ERRHANDLER_FREE
# MPI_ERRHANDLER_F2C
# MPI_ERRHANDLER_C2F
# MPI_ERROR_STRING
# MPI_ERROR_CLASS
# MPI_ADD_ERROR_CLASS
# MPI_REMOVE_ERROR_CLASS
# MPI_ADD_ERROR_CODE
# MPI_REMOVE_ERROR_CODE
# MPI_ADD_ERROR_STRING
# MPI_REMOVE_ERROR_STRING
# ---------------------------------

mpi_thread_safe_function_names= [
    "MPI_Initialized",
    "MPI_Finalized",
    "MPI_Get_version",
    "MPI_Get_library_version",
    "MPI_Add_error_class",
    "MPI_Add_error_code",
    "MPI_Add_error_string",
    "MPI_Remove_error_class",
    "MPI_Remove_error_code",
    "MPI_Remove_error_string",
    "MPI_Errhandler_free",
    "MPI_Errhandler_f2c",
    "MPI_Errhandler_c2f",
    "MPI_Error_string",
    "MPI_Error_class",
    "MPI_Session_create_errhandler",
    "MPI_Session_call_errhandler",
    "MPI_Info_create",
    "MPI_Info_create_env",
    "MPI_Info_set",
    "MPI_Info_delete",
    # "MPI_Info_get",
    "MPI_Info_get_string",
    # "MPI_Info_get_valuelen",
    "MPI_Info_get_nkeys",
    "MPI_Info_get_nthkey",
    "MPI_Info_dup",
    "MPI_Info_free",
    "MPI_Info_f2c",
    "MPI_Info_c2f"
]

mpi_collective_function_names = [
    'MPI_Allgather',
    'MPI_Iallgather',
    'MPI_Allgatherv',
    'MPI_Iallgatherv',
    'MPI_Allreduce',
    'MPI_Iallreduce',
    'MPI_Alltoall',
    'MPI_Ialltoall',
    'MPI_Alltoallv',
    'MPI_Ialltoallv',
    'MPI_Alltoallw',
    'MPI_Ialltoallw',
    'MPI_Barrier',
    'MPI_Ibarrier',
    'MPI_Bcast',
    'MPI_Ibcast',
    'MPI_Exscan',
    'MPI_Iexscan',
    'MPI_Gather',
    'MPI_Igather',
    'MPI_Gatherv',
    'MPI_Igatherv',
    'MPI_Reduce',
    'MPI_Ireduce',
    'MPI_Reduce_scatter',
    'MPI_Ireduce_scatter',
    'MPI_Reduce_scatter_block',
    'MPI_Ireduce_scatter_block',
    'MPI_Scan',
    'MPI_Iscan',
    'MPI_Scatter',
    'MPI_Iscatter',
    'MPI_Scatterv',
    'MPI_Iscatterv'
]

mpi_p2p_function_names = [
    'MPI_Bsend',
    'MPI_Ibsend',
    'MPI_Imrecv',
    'MPI_Irecv',
    'MPI_Irsend',
    'MPI_Isend',
    'MPI_Issend',
    'MPI_Recv',
    'MPI_Rsend',
    'MPI_Send',
    'MPI_Sendrecv',
    'MPI_Sendrecv_replace',
    'MPI_Ssend'
]

mpi_probe_function_names = [
    'MPI_Improbe',
    'MPI_Iprobe',
    'MPI_Mprobe',
    'MPI_Probe'
]

mpi_one_sided_function_names = [
    'MPI_Accumulate',
    'MPI_Compare_and_swap',
    'MPI_Fetch_and_op',
    'MPI_Get',
    'MPI_Get_accumulate',
    'MPI_Put',
    'MPI_Raccumulate',
    'MPI_Rget',
    'MPI_Rget_accumulate',
    'MPI_Rput',
]

mpi_persistent_function_names = [
    'MPI_Bsend_init',
    'MPI_Rsend_init',
    'MPI_Send_init',
    'MPI_Ssend_init',
    'MPI_Recv_init',
    'MPI_Start',
    'MPI_Startall'
]

manually_implemented_function_names = [
    'MPI_Init_thread',
    'MPI_Init',
    'MPI_Finalize',
    'MPI_Test',
    'MPI_Wait',
    'MPI_Waitall',
    # MMCSO_OFFLOAD_NOT_IMPLEMENTED_YET
    'MPI_Initialized',
    'MPI_Finalized',
    'MPI_Is_thread_main',
    'MPI_Query_thread',
    'MPI_Waitany',
    'MPI_Waitsome',
    'MPI_Testall',
    'MPI_Testany',
    'MPI_Test_cancelled',
    'MPI_Testsome',
    'MPI_Probe',
    'MPI_Mprobe'
]

mpi_status_instead_of_request_function_names = [
    'MPI_File_iwrite_shared',
    'MPI_File_iread_shared',
    'MPI_File_iwrite_all',
    'MPI_File_iwrite',
    'MPI_File_iread_all',
    'MPI_File_iread',
    'MPI_File_iwrite_at_all',
    'MPI_File_iwrite_at',
    'MPI_File_iread_at_all',
    'MPI_File_iread_at',
    'MPI_Imrecv',
    'MPI_Irecv'
]

class Parameter:
    def __init__(self, name, parameter_type):
        self.name = name
        self.type = parameter_type

class Function:
    def __init__(self, name, return_type, parameters):
        self.name = name
        self.return_type = return_type
        self.parameters = parameters
        self.nonblocking = False
        self.nonblocking_equivalent = None
        self.mpi_category = None
        self.assumed_thread_safe = False

def extract_functions_with_libclang(header_file):
    index = Index.create()
    translation_unit = index.parse(header_file)

    functions = []
    for cursor in translation_unit.cursor.get_children():
        if cursor.kind == CursorKind.FUNCTION_DECL:
            func_name = cursor.spelling
            func_return_type = cursor.result_type.spelling
            params = [Parameter(param.spelling, param.type.spelling) for param in cursor.get_arguments()]
            functions.append(Function(func_name, func_return_type, params))

    return functions

def find_mpi_header_path():
    try:
        # Run mpicc -show to get the compile command
        result = subprocess.run(["mpicc", "-show"], capture_output=True, text=True, check=True)
        
        # Extract include paths (those starting with -I)
        include_paths = re.findall(r"-I([^\s]+)", result.stdout)
        
        # Check if mpi.h exists in any of the include paths
        for path in include_paths:
            mpi_header = os.path.join(path, 'mpi.h')
            try:
                with open(mpi_header, 'r'):
                    return path
            except FileNotFoundError:
                continue

        return None
    except (subprocess.CalledProcessError, FileNotFoundError):
        return None

def filter_non_mpi_functions(functions):
    return [func for func in functions if func.name.startswith('MPI_')]
    
def filter_thread_safe_functions(functions):
    return [func for func in functions if not func.name in mpi_thread_safe_function_names]
    
def filter_assumed_thread_safe_functions(functions):
    # TODO !
    return functions
    
def filter_non_fortran_functions(functions):
    return [func for func in functions if not func.name.endswith('_f2c') and not func.name.endswith('_c2f')]

def filter_non_tool_functions(functions):
    return [func for func in functions if not func.name.startswith('MPI_T_') and not func.name == 'MPI_Pcontrol']

def filter_non_assumed_unsafe_functions(functions):
    pass # TODO

#########################################################
###   Implementation File Header and Footer
#########################################################

# Header
impl_file_header = f'''\
#include <utility> // std::move

#include "config.h"
#include "mpi_command.h"

#include <mpi.h>

using mmcso::OffloadCommand;
using mmcso::make_mpi_callable;

extern "C" {{
'''

# Footer
impl_file_footer = '''\

} /* extern "C" */

'''

#########################################################
###   Header File Header and Footer
#########################################################

# Header
header_file_header = f'''\
#pragma once

#include <mpi.h>

#include <functional> // bind_front
#include <variant>    // variant
#include "lambda_wrapper.h"

namespace mmcso {{

'''

# Footer
header_file_footer = '''\

} // namespace mmcso

'''
    
#########################################################
###   Function Body Generation
#########################################################

def make_parameter_list(parameters):
    result = []
    for p in parameters:
        if p.type[-1] == ']':
            # handle array types
            pos = p.type.index('[')
            result.append((p.name + p.type[pos:], p.type[:pos]))
        else:
            result.append((p.name, p.type))
        
    return ', '.join([f'{typename} {identifier}' for (identifier, typename) in result])

def make_argument_list(parameters):
    return ', '.join([f'std::move({p.name})' for p in parameters])

def nonblocking_function_body(function, fn_num):
    parameter_list = make_parameter_list(function.parameters)
    argument_list_no_request = make_argument_list(function.parameters[:-1])
    return f'''\

{function.return_type} {function.name}({parameter_list})
{{
    oe.post(OffloadCommand{{make_mpi_callable<{fn_num}, P{function.name}, true>({argument_list_no_request}), {function.parameters[-1].name}}});
    return MPI_SUCCESS;
}}
'''

def blocking_function_body_with_nonblocking_equivalent(fn_blocking, fn_nonblocking):
    parameter_list = make_parameter_list(fn_blocking.parameters)
    argument_list = make_argument_list(fn_blocking.parameters)
    return f'''\

{fn_blocking.return_type} {fn_blocking.name}({parameter_list})
{{
    MPI_Request request_local;
    {fn_nonblocking.name}({argument_list}, &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}}
'''

def nonblocking_function_body_status_no_request(function, fn_num):
    parameter_list = make_parameter_list(function.parameters)
    argument_list = make_argument_list(function.parameters)
    return f'''\

{function.return_type} {function.name}({parameter_list})
{{
    MPI_Request request_local = MPI_REQUEST_NULL; // TODO
    oe.post(OffloadCommand{{make_mpi_callable<{fn_num}, P{function.name}, false>({argument_list}), &request_local}});
    return MPI_SUCCESS;
}}
'''

def blocking_function_body_status_instead_of_request(fn_blocking, fn_nonblocking):
    parameter_list = make_parameter_list(fn_blocking.parameters)
    argument_list = make_argument_list(fn_blocking.parameters[:-1])
    return f'''\

{fn_blocking.return_type} {fn_blocking.name}({parameter_list})
{{
    MPI_Request request_local;
    {fn_nonblocking.name}({argument_list}, &request_local);
    MPI_Wait(&request_local, {fn_blocking.parameters[-1].name}); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}}
'''

def blocking_function_body(function, fn_num):
    parameter_list = make_parameter_list(function.parameters)
    argument_list = make_argument_list(function.parameters)
    return f'''\

{function.return_type} {function.name}({parameter_list})
{{
    MPI_Request request_local;
    oe.post(OffloadCommand{{make_mpi_callable<{fn_num}, P{function.name}, false>({argument_list}), &request_local, true}});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}}

'''

#########################################################
###   MPI Function Parsing and Attribute Setting
#########################################################

def has_request(function):
    if not function.parameters:
        return False
    return function.parameters[-1].type == 'MPI_Request *'

def has_status(function):
    return function.parameters[-1].type == 'MPI_Status *'

def nonblocking_has_request_blocking_has_status(fn_blocking, fn_nonblocking):
    return len(fn_nonblocking.parameters) == len(fn_blocking.parameters) and \
        has_request(fn_nonblocking) and has_status(fn_blocking)

def set_nonblocking_blocking_pairs(functions):

    def indexes_of_i(s):
        positions = [index for index, char in enumerate(s) if char.lower() == 'i']
        return positions

    def first_equal_with_extra_i(s1, s2):
        # If length difference isn't exactly 1, return False
        if abs(len(s1) - len(s2)) != 1:
            return False

        # Determine which string is longer
        longer, shorter = (s1, s2) if len(s1) > len(s2) else (s2, s1)

        # Get occurrences of 'i' from the longer string and compare
        for index_of_i in indexes_of_i(longer):
            reconstructed = longer[:index_of_i] + longer[index_of_i + 1:]
            if reconstructed == shorter:
                return True
        return False

    # result = []
    
    for i, f1 in enumerate(functions):
        string = f1.name
        # Check against all other strings
        for j, f2 in enumerate(functions):
            if j <= i:
                continue
            compare = f2.name

            if first_equal_with_extra_i(string[4:].lower(), compare[4:].lower()):
                (fn_blocking, fn_nonblocking) = (f2, f1) if len(f1.name) > len(f2.name) else (f1, f2)
                
                # Set function attributes
                fn_blocking.nonblocking_equivalent = fn_nonblocking
                fn_nonblocking.nonblocking = True
                break

#########################################################
###   Variant Type Helpers
#########################################################

def make_bind_type(function, fn_num):
    def make_decay_t_argument_list(parameters):
        return ', '.join([f'std::decay_t<{p.type}>{{}}' for p in parameters])

    # print(function.name)
    parameters = function.parameters[:-1]  if has_request(function) else function.parameters

    argument_list = make_decay_t_argument_list(parameters)
    tf = 'true' if has_request(function) else 'false'

    return f'    using T{fn_num} = decltype(mmcso::make_lambda_wrapper<P{function.name}, {tf}>({argument_list}));\n'

def make_variant_type_definition(num_fns):
    variant_type = ('using variant_type = std::variant<std::monostate,\n')
    for i in range(1, num_fns):
        variant_type = variant_type + f'T{i},\n'
    variant_type = variant_type[:-2] + '\n>;\n'
    variant_type = variant_type + f'static_assert(std::variant_size_v<variant_type> == {num_fns});\n'

    for i in range(1, num_fns):
        variant_type = variant_type + (f'static_assert(std::is_same_v<T{i}, std::variant_alternative_t<{i}, variant_type>>);\n')
    
    return variant_type

#########################################################
###   MPI Implementation and Variant Type Header
#########################################################

def generate_cpp_files(functions, impl_file, header_file):
    implemented_functions = []

    impl_file.write(impl_file_header)
    header_file.write(header_file_header)
    
    # need to start from one because first variant member type must be
    # std::monostate to make variant default-constructible
    fn_num = 1

    for f in functions:

        if f.nonblocking:

            # nonblocking function w/o request (e.g. Iprobe, Improbe)
            if not has_request(f):
                impl_file.write(nonblocking_function_body_status_no_request(f, fn_num))
                # MPI_Probe is manually implemented

            # typical nonblocking function
            else:
                impl_file.write(nonblocking_function_body(f, fn_num))

            implemented_functions.append(f)
            header_file.write(make_bind_type(f, fn_num))
            fn_num = fn_num + 1

        else: # blocking function

            # blocking function with nonblocking equivalent
            #
            # ==> blocking function can be implemented
            # in terms of their nonblocking equivalent
            if f.nonblocking_equivalent != None:
                
                if not has_request(f.nonblocking_equivalent):
                    continue

                # blocking function has status instead of request
                if nonblocking_has_request_blocking_has_status(f, f.nonblocking_equivalent):
                    impl_file.write(blocking_function_body_status_instead_of_request(f, f.nonblocking_equivalent))

                # nonblocking == blocking + request
                else:
                    impl_file.write(blocking_function_body_with_nonblocking_equivalent(f, f.nonblocking_equivalent))
                    
                implemented_functions.append(f)

            # some functions like e.g. MPI_Get_processor_name may be assumed thread safe
            elif f.assumed_thread_safe:
                # don't increase fn_num
                # TODO: define thread safe functions
                continue

            # blocking function without nonblocking equivalent
            else:
                # TODO: handling of those functions
                
                if has_request(f):
                    print('skipping: ' + f.name)
                    continue
                
                continue
                
                impl_file.write(blocking_function_body(f, fn_num))
                implemented_functions.append(f)
                header_file.write(make_bind_type(f, fn_num))
                fn_num = fn_num + 1

    header_file.write(make_variant_type_definition(fn_num))

    impl_file.write(impl_file_footer)
    header_file.write(header_file_footer)

    return implemented_functions

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("-p", "--path", type=str, default='', help="output path")
    args = parser.parse_args()

    mpi_path = find_mpi_header_path()
    if mpi_path:
        print(f"MPI header found in: {mpi_path}")
    else:
        print("MPI header not found.")

    functions = extract_functions_with_libclang(os.path.join(mpi_path, 'mpi.h'))

    functions = filter_non_mpi_functions(functions)
    functions = filter_thread_safe_functions(functions)
    functions = filter_assumed_thread_safe_functions(functions)
    functions = filter_non_fortran_functions(functions)
    functions = filter_non_tool_functions(functions)

    set_nonblocking_blocking_pairs(functions)

    manually_implemented_functions = [f for f in functions if f.name in manually_implemented_function_names]
    functions = [f for f in functions if f.name not in manually_implemented_function_names]

    variant_header_path = os.path.join(args.path, 'variant_type.h')
    mpi_impl_path = os.path.join(args.path, 'mpi_impl.cpp')

    impl_file = open(mpi_impl_path, 'w')
    header_file = open(variant_header_path, 'w')

    implemented_functions = generate_cpp_files(functions, impl_file, header_file)

    impl_file.close()
    header_file.close()

    implemented_functions = implemented_functions + manually_implemented_functions

    # print('\n\nImplemented functions:\n\n' + '\n'.join(mpi_implemented_function_names))
    unimplemented = [f for f in functions if f not in implemented_functions]
    # print('\n\nUnimplemented functions:\n\n' + '\n'.join([f.name for f in unimplemented]))
    
    unimplemented_with_request = [f for f in unimplemented if 'MPI_Request *' in [p.type for p in f.parameters]]
    # print('\nWith request:\n')
    # print('\n'.join([f.name for f in unimplemented_with_request]))

    unimplemented_without_request = [f for f in unimplemented if f not in unimplemented_with_request]
    # print('\nWithout request:\n')
    # print('\n'.join([f.name for f in unimplemented_without_request]))

    
"""
With request:

MPI_Bsend_init
MPI_Cancel
MPI_Grequest_start
MPI_Raccumulate
MPI_Recv_init
MPI_Request_free
MPI_Rget
MPI_Rget_accumulate
MPI_Rput
MPI_Rsend_init
MPI_Send_init
MPI_Ssend_init
MPI_Start

Without request:

MPI_Abort
MPI_Accumulate
MPI_Alloc_mem
MPI_Buffer_attach
MPI_Buffer_detach
MPI_Cart_coords*
MPI_Cart_create
MPI_Cart_get*
MPI_Cart_map
MPI_Cart_rank*
MPI_Cart_shift*
MPI_Cart_sub
MPI_Cartdim_get*
MPI_Close_port
MPI_Comm_accept
MPI_Comm_call_errhandler
MPI_Comm_compare
MPI_Comm_connect
MPI_Comm_create_errhandler
MPI_Comm_create_keyval
MPI_Comm_create_group
MPI_Comm_create
MPI_Comm_delete_attr
MPI_Comm_disconnect
MPI_Comm_dup_with_info
MPI_Comm_free_keyval
MPI_Comm_free
MPI_Comm_get_attr
MPI_Dist_graph_create
MPI_Dist_graph_create_adjacent
MPI_Dist_graph_neighbors*
MPI_Dist_graph_neighbors_count*
MPI_Comm_get_errhandler*
MPI_Comm_get_info*
MPI_Comm_get_name*
MPI_Comm_get_parent*
MPI_Comm_group*
MPI_Comm_join
MPI_Comm_rank*
MPI_Comm_remote_group
MPI_Comm_remote_size
MPI_Comm_set_attr
MPI_Comm_set_errhandler
MPI_Comm_set_info
MPI_Comm_set_name
MPI_Comm_size*
MPI_Comm_spawn
MPI_Comm_spawn_multiple
MPI_Comm_split
MPI_Comm_split_type
MPI_Comm_test_inter
MPI_Compare_and_swap
MPI_Dims_create


MPI_Fetch_and_op
MPI_File_call_errhandler
MPI_File_create_errhandler
MPI_File_set_errhandler
MPI_File_get_errhandler
MPI_File_open
MPI_File_close
MPI_File_delete
MPI_File_set_size
MPI_File_preallocate
MPI_File_get_size
MPI_File_get_group
MPI_File_get_amode
MPI_File_set_info
MPI_File_get_info
MPI_File_set_view
MPI_File_get_view
MPI_File_seek
MPI_File_get_position
MPI_File_get_byte_offset
MPI_File_read_ordered
MPI_File_write_ordered
MPI_File_seek_shared
MPI_File_get_position_shared
MPI_File_read_at_all_begin
MPI_File_read_at_all_end
MPI_File_write_at_all_begin
MPI_File_write_at_all_end
MPI_File_read_all_begin
MPI_File_read_all_end
MPI_File_write_all_begin
MPI_File_write_all_end
MPI_File_read_ordered_begin
MPI_File_read_ordered_end
MPI_File_write_ordered_begin
MPI_File_write_ordered_end
MPI_File_get_type_extent
MPI_File_set_atomicity
MPI_File_get_atomicity
MPI_File_sync
MPI_Free_mem  ######################## checked
MPI_Get_address*
MPI_Get_count*
MPI_Get_elements*
MPI_Get_elements_x*
MPI_Get
MPI_Get_accumulate

MPI_Get_processor_name*
MPI_Graph_create
MPI_Graph_get
MPI_Graph_map
MPI_Graph_neighbors_count
MPI_Graph_neighbors
MPI_Graphdims_get
MPI_Grequest_complete
MPI_Group_compare
MPI_Group_difference
MPI_Group_excl
MPI_Group_free
MPI_Group_incl
MPI_Group_intersection
MPI_Group_range_excl
MPI_Group_range_incl
MPI_Group_rank
MPI_Group_size
MPI_Group_translate_ranks
MPI_Group_union
MPI_Info_create
MPI_Info_delete
MPI_Info_dup
MPI_Info_free
MPI_Info_get
MPI_Info_get_nkeys
MPI_Info_get_nthkey
MPI_Info_get_valuelen
MPI_Info_set
MPI_Intercomm_create
MPI_Intercomm_merge
MPI_Lookup_name
MPI_Op_commutative
MPI_Op_create
MPI_Open_port
MPI_Op_free
MPI_Pack_external
MPI_Pack_external_size
MPI_Pack
MPI_Pack_size
MPI_Pcontrol
MPI_Publish_name
MPI_Put
MPI_Reduce_local
MPI_Register_datarep
MPI_Request_get_status
MPI_Sendrecv
MPI_Sendrecv_replace
MPI_Startall
MPI_Status_set_cancelled
MPI_Status_set_elements
MPI_Status_set_elements_x
MPI_Topo_test
MPI_Type_commit
MPI_Type_contiguous
MPI_Type_create_darray
MPI_Type_create_f90_complex
MPI_Type_create_f90_integer
MPI_Type_create_f90_real
MPI_Type_create_hindexed_block
MPI_Type_create_hindexed
MPI_Type_create_hvector
MPI_Type_create_keyval
MPI_Type_create_indexed_block
MPI_Type_create_struct
MPI_Type_create_subarray
MPI_Type_create_resized
MPI_Type_delete_attr
MPI_Type_dup
MPI_Type_free
MPI_Type_free_keyval
MPI_Type_get_attr
MPI_Type_get_contents
MPI_Type_get_envelope
MPI_Type_get_extent
MPI_Type_get_extent_x
MPI_Type_get_name
MPI_Type_get_true_extent
MPI_Type_get_true_extent_x
MPI_Type_indexed
MPI_Type_match_size
MPI_Type_set_attr
MPI_Type_set_name
MPI_Type_size
MPI_Type_size_x
MPI_Type_vector
MPI_Unpack
MPI_Unpublish_name
MPI_Unpack_external
MPI_Win_allocate
MPI_Win_allocate_shared
MPI_Win_attach
MPI_Win_call_errhandler
MPI_Win_complete
MPI_Win_create
MPI_Win_create_dynamic
MPI_Win_create_errhandler
MPI_Win_create_keyval
MPI_Win_delete_attr
MPI_Win_detach
MPI_Win_fence
MPI_Win_flush
MPI_Win_flush_all
MPI_Win_flush_local
MPI_Win_flush_local_all
MPI_Win_free
MPI_Win_free_keyval
MPI_Win_get_attr
MPI_Win_get_errhandler
MPI_Win_get_group
MPI_Win_get_info
MPI_Win_get_name
MPI_Win_lock
MPI_Win_lock_all
MPI_Win_post
MPI_Win_set_attr
MPI_Win_set_errhandler
MPI_Win_set_info
MPI_Win_set_name
MPI_Win_shared_query
MPI_Win_start
MPI_Win_sync
MPI_Win_test
MPI_Win_unlock
MPI_Win_unlock_all
MPI_Win_wait
MPI_Wtick*
MPI_Wtime*
MPI_Attr_delete
MPI_Attr_get
MPI_Attr_put
MPI_Keyval_create
MPI_Keyval_free
"""










# MPI Categories:
#
# P2P
# Collective
# RMA
# Persistent (Partitioned)

"""
def get_mpi_category(function):
    if function.name.startswith('MPI_Info_'):
        return 'Info'
    elif function.name.startswith('MPI_Type_'):
        return 'Type'
    elif function.name.startswith('MPI_Status_'):
        return 'Status'
    elif function.name.startswith('MPI_Win_'):
    elif function.name.startswith('MPI_Op_'):
    elif function.name.startswith('MPI_File_'):
    elif function.name.startswith('MPI_Comm_'):
    elif function.name.startswith('MPI_Cart'):
    elif function.name.startswith('MPI_Add_error'):
    elif function.name.startswith(''):
    elif function.name.startswith(''):
    elif function.name.startswith(''):
"""

"""
mpi_info_functions = [func for func in mpi_functions if func.name.startswith('MPI_Info_')]
mpi_type_functions = [func for func in mpi_functions if func.name.startswith('MPI_Type_')]
mpi_status_functions = [func for func in mpi_functions if func.name.startswith('MPI_Status_')]
mpi_window_functions = [func for func in mpi_functions if func.name.startswith('MPI_Win_')]
mpi_op_functions = [func for func in mpi_functions if func.name.startswith('MPI_Op_')]
mpi_file_functions = [func for func in mpi_functions if func.name.startswith('MPI_File_')]
mpi_comm_functions = [func for func in mpi_functions if func.name.startswith('MPI_Comm_')]
mpi_cart_functions = [func for func in mpi_functions if func.name.startswith('MPI_Cart')]
mpi_add_error_functions = [func for func in mpi_functions if func.name.startswith('MPI_Add_error')]
mpi_group_functions = [func for func in mpi_functions if func.name.startswith('MPI_Group_')]
mpi_dist_graph_functions = [func for func in mpi_functions if func.name.startswith('MPI_Dist_graph_')]
mpi_neighbor_collective_functions = [func for func in mpi_functions if func.name.startswith('MPI_Neighbor_') or func.name.startswith('MPI_Ineighbor_')]
mpi_graph_functions = [func for func in mpi_functions if func.name.startswith('MPI_Neighbor_') or func.name.startswith('MPI_Graph')]
mpi_get_functions = [func for func in mpi_functions if func.name.startswith('MPI_Get_') and func.name != 'MPI_Get_accumulate']
mpi_collective_functions = [func for func in mpi_functions if func.name in mpi_collective_function_names]
mpi_p2p_functions = [func for func in mpi_functions if func.name in mpi_p2p_function_names]
mpi_probe_functions = [func for func in mpi_functions if func.name in mpi_probe_function_names]
mpi_one_sided_functions = [func for func in mpi_functions if func.name in mpi_one_sided_function_names]
mpi_persistent_functions = [func for func in mpi_functions if func.name in mpi_persistent_function_names]
mpi_manually_implemented_functions = [func for func in mpi_functions if func.name in mpi_manually_implemented_function_names]
"""



"""
mpi_filtered_functions = [] \
    + mpi_info_functions \
    + mpi_type_functions \
    + mpi_status_functions \
    + mpi_window_functions \
    + mpi_op_functions \
    + mpi_file_functions \
    + mpi_comm_functions \
    + mpi_cart_functions \
    + mpi_add_error_functions \
    + mpi_group_functions \
    + mpi_dist_graph_functions \
    + mpi_collective_functions \
    + mpi_neighbor_collective_functions \
    + mpi_p2p_functions \
    + mpi_graph_functions \
    + mpi_probe_functions \
    + mpi_one_sided_functions \
    + mpi_get_functions \
    + mpi_persistent_functions \
    + mpi_manually_implemented_functions

mpi_remaining_functions = [func for func in mpi_functions if func not in mpi_filtered_functions]

for func in mpi_remaining_functions:
    print("Functions not yet considered:")
    print(f"{func.name}")
"""
