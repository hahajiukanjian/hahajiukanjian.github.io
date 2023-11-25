```shell
wpa_passphrase WIFI_Name WIFI_Passwd > internet.conf

wpa_supplicant -c internet.conf -i device(wlan0) &

dhcpcd &
```
`&`表示在背后运行
dhcpcd 动态分配IP地址
