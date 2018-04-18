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
    name = 'client_parallel',
    srcs = [
        'client_parallel.cc'
    ],
    deps = [
        ':echo_service_proto',
        '//trident:trident',
    ]
)

cc_binary(
    name = 'client_serial',
    srcs = [
        'client_serial.cc'
    ],
    deps = [
        ':echo_service_proto',
        '//toft/base:random',
        '//toft/net/http:http_client',
        '//toft/system/threading:threading',
        '//trident:trident',
    ]
)

cc_binary(
    name = 'echo_server',
    srcs = [
        'echo_server.cc'
    ],
    deps = [
        ':echo_service_proto',
        '//trident:trident',
    ]
)
