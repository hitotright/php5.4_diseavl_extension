# this extension disable php5.4 eval function

```shell
phpize
./configure --with-php-config=/usr/bin/php-config
make
make install
```

add php.ini
extension=diseval.so
