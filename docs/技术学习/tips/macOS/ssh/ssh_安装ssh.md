安装ssh
``` bash
pacman -Syy openssh
```

``` bash
sudo vim /etc/ssh/sshd_config
#开启
PermitRootLogin yes
```

启动服务
``` bash
systemctl start sshd
```

开机启动
``` bash
systemctl enable sshd.service
```