# Server

服务端框架

## I 依赖
- sqlite3
- google-protobuf
- nlohmann_json
- spdlog
- asio

## II 使用方式
``` bash
$ ./Server <options> (-h help | -l loglevel | -p plugin)"
```

## III 项目结构

### Common

存放通用插件
- Log: 日志插件
- NetPlugin: 网络通信插件
- NetMsgDefine: 网络通信数据定义
- SQLPlugin: 数据库插件

### GameServer

核心部分, 程序入口

### Resources

用来存放资源文件
- Configs: 配置文件, 如Plugins.json
- Logs: 存放日志文件

### Plugins
相应插件目录

- DemoPlugin: 示例插件
- UserPlugin: 管理用户登录, 注册

### 3rdParty
第三方依赖
