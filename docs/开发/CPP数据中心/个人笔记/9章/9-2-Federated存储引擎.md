Federated引擎从远程服务器获取所有行，然后在本地进行过滤。

Federated引擎仅支持主键和唯一键索引，不支持普通索引

## 使用`主键和普通索引`在`远程与本地`进行查询对比
- 下面示例在远程服务器的表`T_ZHOBTMIND1`上进行查询时，用到主键和用到普通索引的情况
obtid为主键
t 为普通索引
```sql
mysql> EXPLAIN select * from T_ZHOBTMIND1 where obtid='59493';
+----+-------------+--------------+------------+------+--------------------------+---------+---------+-------+------+----------+-------+
| id | select_type | table        | partitions | type | possible_keys            | key     | key_len | ref   | rows | filtered | Extra |
+----+-------------+--------------+------------+------+--------------------------+---------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | T_ZHOBTMIND1 | NULL       | ref  | PRIMARY,IDX_ZHOBTMIND1_3 | PRIMARY | 42      | const |    3 |   100.00 | NULL  |
+----+-------------+--------------+------------+------+--------------------------+---------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.00 sec)

mysql> EXPLAIN select * from T_ZHOBTMIND1 where t>100;
+----+-------------+--------------+------------+------+------------------+------+---------+------+------+----------+-------------+
| id | select_type | table        | partitions | type | possible_keys    | key  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+--------------+------------+------+------------------+------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | T_ZHOBTMIND1 | NULL       | ALL  | IDX_ZHOBTMIND1_4 | NULL | NULL    | NULL | 2517 |    71.12 | Using where |
+----+-------------+--------------+------------+------+------------------+------+---------+------+------+----------+-------------+
1 row in set, 1 warning (0.00 sec)
```
其中 使用使用普通索引 t 进行查询时， `possible_keys`的值为`IDX_ZHOBTMIND1_4`

- 下面示例在本地的表`LK_ZHOBTMIND1`上进行查询时，用到主键和用到普通索引的情况
obtid为主键
t 为普通索引
```sql
mysql> EXPLAIN select * from LK_ZHOBTMIND1 where obtid='59493';
+----+-------------+---------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
| id | select_type | table         | partitions | type | possible_keys | key     | key_len | ref   | rows | filtered | Extra |
+----+-------------+---------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | LK_ZHOBTMIND1 | NULL       | ref  | PRIMARY       | PRIMARY | 32      | const |    2 |   100.00 | NULL  |
+----+-------------+---------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.01 sec)

mysql> EXPLAIN select * from LK_ZHOBTMIND1 where t>100;
+----+-------------+---------------+------------+------+---------------+------+---------+------+------+----------+-------------+
| id | select_type | table         | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+---------------+------------+------+---------------+------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | LK_ZHOBTMIND1 | NULL       | ALL  | NULL          | NULL | NULL    | NULL | 2517 |    33.33 | Using where |
+----+-------------+---------------+------------+------+---------------+------+---------+------+------+----------+-------------+
1 row in set, 1 warning (0.00 sec)
```
其中 使用使用普通索引 t 进行查询时， `possible_keys`的值为`空`

## 使用`唯一键`在`远程与本地`进行查询对比
可以看到，它们使用的possible_keys都是唯一键
```sql
mysql> EXPLAIN select * from T_ZHOBTMIND1 where keyid=12200761;
+----+-------------+--------------+------------+-------+------------------+------------------+---------+-------+------+----------+-------+
| id | select_type | table        | partitions | type  | possible_keys    | key              | key_len | ref   | rows | filtered | Extra |
+----+-------------+--------------+------------+-------+------------------+------------------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | T_ZHOBTMIND1 | NULL       | const | ZHOBTMIND1_KEYID | ZHOBTMIND1_KEYID | 8       | const |    1 |   100.00 | NULL  |
+----+-------------+--------------+------------+-------+------------------+------------------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.00 sec)
```

```sql
mysql> EXPLAIN select * from LK_ZHOBTMIND1 where keyid=12200761;;
+----+-------------+---------------+------------+-------+------------------+------------------+---------+-------+------+----------+-------+
| id | select_type | table         | partitions | type  | possible_keys    | key              | key_len | ref   | rows | filtered | Extra |
+----+-------------+---------------+------------+-------+------------------+------------------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | LK_ZHOBTMIND1 | NULL       | const | ZHOBTMIND1_KEYID | ZHOBTMIND1_KEYID | 8       | const |    1 |   100.00 | NULL  |
+----+-------------+---------------+------------+-------+------------------+------------------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.00 sec)
```
<br>

> 创建Federated表时，必须要指定主键和唯一键，否则会导致查询的性能大幅下降
> - 要这样
> ``` sql
> CREATE TABLE `LK_ZHOBTMIND1`
> (
>   `obtid`           varchar(10) NOT NULL               COMMENT '站点代码。',
>   `ddatetime`       datetime NOT NULL                  COMMENT '数据时间，精确到分钟。',
>   `t`               int(11) DEFAULT NULL               COMMENT '湿度，单位：0.1摄氏度。',
>   `p`               int(11) DEFAULT NULL               COMMENT '气压，单位：0.1百帕。',
>   `u`               int(11) DEFAULT NULL               COMMENT '相对湿度，0-100之间的值。',
>   `wd`              int(11) DEFAULT NULL               COMMENT '风向，0-360之间的值。',
>   `wf`              int(11) DEFAULT NULL               COMMENT '风速：单位0.1m/s。',
>   `r`               int(11) DEFAULT NULL               COMMENT '降雨量：0.1mm。',
>   `vis`             int(11) DEFAULT NULL               COMMENT '能见度：0.1米。',
>   `upttime`         timestamp NOT NULL                 COMMENT '更新时间。',
>   `keyid`           bigint(20) NOT NULL AUTO_INCREMENT COMMENT '记录编号，自动增长列。',
>   PRIMARY KEY (`obtid`,`ddatetime`),
>   UNIQUE KEY `ZHOBTMIND1_KEYID` (`keyid`)
> ) ENGINE=FEDERATED CONNECTION='mysql://root:DYT.9525ing@127.0.0.1:3306/TestDB/T_ZHOBTMIND1';
> ```
> - 不能这样
> ``` sql
> CREATE TABLE `LK_ZHOBTMIND1`
> (
>   `obtid`           varchar(10) NOT NULL               COMMENT '站点代码。',
>   `ddatetime`       datetime NOT NULL                  COMMENT '数据时间，精确到分钟。',
>   `t`               int(11) DEFAULT NULL               COMMENT '湿度，单位：0.1摄氏度。',
>   `p`               int(11) DEFAULT NULL               COMMENT '气压，单位：0.1百帕。',
>   `u`               int(11) DEFAULT NULL               COMMENT '相对湿度，0-100之间的值。',
>   `wd`              int(11) DEFAULT NULL               COMMENT '风向，0-360之间的值。',
>   `wf`              int(11) DEFAULT NULL               COMMENT '风速：单位0.1m/s。',
>   `r`               int(11) DEFAULT NULL               COMMENT '降雨量：0.1mm。',
>   `vis`             int(11) DEFAULT NULL               COMMENT '能见度：0.1米。',
>   `upttime`         timestamp NOT NULL                 COMMENT '更新时间。',
>   `keyid`           bigint(20) NOT NULL                COMMENT '记录编号，自动增长列。'
> ) ENGINE=FEDERATED CONNECTION='mysql://root:DYT.9525ing@127.0.0.1:3306/TestDB/T_ZHOBTMIND1';
> ```