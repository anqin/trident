proto_library(
    name = 'sleep_service_proto',
    srcs = 'sleep_service.proto'
)

cc_binary(
    name = 'sleep_client',
    srcs = [
        'client.cc'
    ],
    deps = [
        ':sleep_service_proto',
        '//trident:trident'
    ]
)

cc_binary(
    name = 'sleep_server',
    srcs = [
        'server.cc'
    ],
    deps = [
        ':sleep_service_proto',
        '//trident:trident'
    ]
)
