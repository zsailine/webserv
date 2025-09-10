# docker build -t siege-test .


docker run --rm siege-test -c 10 http://192.168.122.1:8080/index.php

