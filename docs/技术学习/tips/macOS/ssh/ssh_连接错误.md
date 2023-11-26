```shell
~
➜ ssh root@192.168.0.104
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the ED25519 key sent by the remote host is
SHA256:TUe63//TeXi5dQHKYtWW21/SEtCY2oVZ6Xf+pbdDDcI.
Please contact your system administrator.
Add correct host key in /Users/hahajiukanjian/.ssh/known_hosts to get rid of this message.
Offending ECDSA key in /Users/hahajiukanjian/.ssh/known_hosts:37
Host key for 192.168.0.104 has changed and you have requested strict checking.
Host key verification failed.
```

解决办法：
ssh-keygen -R +输入服务器的IP
