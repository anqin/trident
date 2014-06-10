proto_library(
    name = 'echo_service_proto',
    srcs = [
        'echo_service.proto'
    ],
    deps = [
        '//trident:rpc_option_proto'
    ]
)

cc_binary(
    name = 'echo_server',
    srcs = 'server.cc',
    deps = [
        ':echo_service_proto',
        '//trident:trident'
    ]
)

cc_binary(
    name = 'echo_client_sync',
    srcs = 'client_sync.cc',
    deps = [
        ':echo_service_proto',
        '//trident:trident'
    ]
)
