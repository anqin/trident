proto_library(
    name = 'rpc_option_proto',
    srcs = [
        'rpc_meta.proto',
        'rpc_option.proto'
    ]
)

proto_library(
    name = 'builtin_service_proto',
    srcs = [
        'builtin_service.proto'
    ],
    deps = [
        ':rpc_option_proto'
    ]
)

cc_library(
    name = 'snappy',
    srcs = [
        'snappy/snappy.cc',
        'snappy/snappy-sinksource.cc',
        'snappy/snappy-stubs-internal.cc'
    ],
    warning='no'
)

cc_library(
    name = 'trident',
    srcs = [
        'binary_rpc_request.cc',
        'binary_rpc_request_parser.cc',
        'block_wrappers.cc',
        'boost_system_error_code.cc',
        'buffer.cc',
        'builtin_service_impl.cc',
        'builtin_service.pb.cc',
        'common.cc',
        'common_internal.cc',
        'compressed_stream.cc',
        'gzip_stream.cc',
        'http_rpc_request.cc',
        'http_rpc_request_parser.cc',
        'lz4.cc',
        'mock_test_helper.cc',
        'pbjson.cc',
        'rpc_channel.cc',
        'rpc_channel_impl.cc',
        'rpc_client.cc',
        'rpc_client_impl.cc',
        'rpc_controller.cc',
        'rpc_endpoint.cc',
        'rpc_error_code.cc',
        'rpc_meta.pb.cc',
        'rpc_option.pb.cc',
        'rpc_request.cc',
        'rpc_request_parser.cc',
        'rpc_server.cc',
        'rpc_server_impl.cc',
        'string_utils.cc',
        'thread_group.cc',
        'timeout_manager.cc',
        'timeout_manager_impl.cc',
        'web_service.cc'
    ],
    deps = [
        ':rpc_option_proto',
        ':builtin_service_proto',
        ':snappy'
    ],
    incs = ['asio']
)

cc_test(
    name = 'atomic_test',
    srcs = 'atomic_test.cc',
    deps = [
        ':trident'
    ]
)

proto_library(
    name = 'test_data_proto',
    srcs = 'test_data.proto',
)

cc_test(
    name = 'buffer_test',
    srcs = 'buffer_test.cc',
    deps = [
        ':test_data_proto',
        ':trident'
    ],
    incs = ['asio'],
)

cc_test(
    name = 'closure_test',
    srcs = 'closure_test.cc',
    deps = [
        ':trident'
    ]
)

cc_test(
    name = 'common_test',
    srcs = 'common_test.cc',
    deps = [
        ':trident'
    ]
)

cc_test(
    name = 'epoll_support_test',
    srcs = 'epoll_support_test.cc',
    deps = [
        ':trident'
    ],
    incs = ['asio']
)

cc_test(
    name = 'ext_closure_test',
    srcs = 'ext_closure_test.cc',
    deps = [
        ':trident'
    ]
)

cc_test(
    name = 'thread_group_test',
    srcs = 'thread_group_test.cc',
    deps = [
        ':trident'
    ]
)

cc_test(
    name = 'timeout_manager_test',
    srcs = 'timeout_manager_test.cc',
    deps = [
        ':trident'
    ]
)

cc_test(
    name = 'tran_buf_pool_test',
    srcs = 'tran_buf_pool_test.cc',
    deps = [
        ':trident'
    ],
    incs = ['asio']
)

cc_test(
    name = 'web_service_test',
    srcs = 'web_service_test.cc',
    deps = [
        ':trident'
    ],
    incs = ['asio']
)

