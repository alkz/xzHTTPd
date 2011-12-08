
echo "Compilig..."
g++ `nspr-config --cflags --libs` -g -o /usr/bin/xzHTTPd ./src/*.cpp ./src/*.hpp

useradd -m xzhttpd
mkdir /home/xzhttpd/htdocs
mkdir /home/xzhttpd/logs

cp ./etc/xzHTTPd.conf /etc
chown xzhttpd:xzhttpd /etc/xzHTTPd.conf

chown xzhttpd:xzhttpd /usr/bin/xzHTTPd

echo "Installed"
