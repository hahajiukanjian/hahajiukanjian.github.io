vi /etc/ssh/sshd_config

```shell
PermitRootLogin yes #允许root登录
PasswordAuthentication yes #允许密码登录
```

重启sshd
`systemctl restart sshd`
