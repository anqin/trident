proto_library(
    name = 'echo_service_proto',
    srcs = 'echo_service.proto'
)

cc_binary(
    name = 'compress_client',
    srcs = [
        'client.cc'
    ],
    deps = [
        ':echo_service_proto',
        '//trident:trident'
    ]
)

cc_binary(
    name = 'compress_server',
    srcs = [
        'server.cc'
    ],
    deps = [
        ':echo_service_proto',
        '//trident:trident'
    ]
)
