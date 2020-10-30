一、src
纯C语言写的http client,支持 https，
支持GET 
支持完整的POST(post的body可输入)

#功能
支持GET POST语义 
内置支持https 支持多平台(window linux) 

https库使用krypton https://github.com/cesanta/krypton
http解析部分使用http_parser https://github.com/nodejs/http-parser
client源码来自https://gitee.com/linxyruffy/httpclient

二、src.single-file
纯C语言写的单文件(头文件和.c文件各一个)的http client,
支持GET 
支持完整的POST(post的body可输入)

