
#### insert into girls(id,name,weight,btime) values(?,?,?,str_to_date(?,'%Y-%m-%d %H:%i:%s'))<br>1366,Incorrect string value: '\xE8\xA5\xBF\xE6\x96\xBD...' for column 'name' at row 1

这个错误是因为你尝试向一个使用utf8字符集的表中插入了一个不能被正确解码的字符串，常见的原因是插入的字符串与表的字符集不匹配。

你可以尝试在插入之前设置连接的字符集为utf8，例如：

```sql
SET NAMES utf8;
```
另外，还需要确保表的字符集为utf8，可以通过以下语句进行修改：

```sql
ALTER TABLE girls CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;
```
如果这些操作还是不能解决问题，可能需要检查一下插入的字符串是否被正确编码为utf8。