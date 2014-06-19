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
        'block_wrappers.cc',
        'boost_system_error_code.cc',
        'buffer.cc',
        'builtin_service_impl.cc',
        'builtin_service.pb.cc',
        'common.cc',
        'common_internal.cc',
        'compressed_stream.cc',
        'gzip_stream.cc',
        'lz4.cc',
        'mock_test_helper.cc',
        'rpc_channel.cc',
        'rpc_channel_impl.cc',
        'rpc_client.cc',
        'rpc_client_impl.cc',
        'rpc_controller.cc',
        'rpc_endpoint.cc',
        'rpc_error_code.cc',
        'rpc_meta.pb.cc',
        'rpc_option.pb.cc',
        'rpc_server.cc',
        'rpc_server_impl.cc',
        'thread_group.cc',
        'timeout_manager.cc',
        'timeout_manager_impl.cc',
    ],
    deps = [
        ':rpc_option_proto',
        ':builtin_service_proto',
        ':snappy'
    ],
    incs = ['asio']
)
