
echo
echo "Compilig..."
echo "g++ \`nspr-config --cflags --libs\` -g -o /usr/bin/xzHTTPd ./src/*.cpp ./src/*.hpp"
g++ `nspr-config --cflags --libs` -g -o /usr/bin/xzHTTPd ./src/*.cpp ./src/*.hpp
echo "Compiled!"
echo
echo "Creating user and directories..."

useradd -m xzhttpd
passwd  -d xzhttpd

mkdir /home/xzhttpd/htdocs
mkdir /home/xzhttpd/logs
mkdir /etc/xzHTTPd/
cp    ./etc/xzHTTPd.conf    /etc/xzHTTPd
cp    ./etc/index.html      /home/xzhttpd/htdocs
cp    ./etc/nishinoav.png   /home/xzhttpd/htdocs

echo
echo "Done!"
echo
echo "Setting permissions..."

chown -R xzhttpd:xzhttpd   /etc/xzHTTPd
chown    xzhttpd:xzhttpd   /usr/bin/xzHTTPd
chown -R xzhttpd:xzhttpd   /home/xzhttpd

echo
echo "--------------------------------------------------------"
echo
echo "xzHTTPd Installed! Enjoy it!"
echo
echo "bin:               /usr/bin/xzHTTPd" 
echo "conf:     /etc/xzHTTPd/xzHTTPd.conf" 
echo "user:                       xzhttpd"
echo "group:                      xzhttpd"
echo "htdocs:        /home/xzhttpd/htdocs"
echo "logs:            /home/xzhttpd/logs"
echo
echo "--------------------------------------------------------"
echo
