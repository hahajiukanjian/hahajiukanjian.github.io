Oracle 在 prepare sql 语句之后，stmt.m_cda.rpc 不会记录错误代码，而 mysql 会记录错误代码

因此判断错误代码的流程需要放在执行(execute)Oracle的sql语句之后