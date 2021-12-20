Run a MariaDB Database:

docker run -dp 3306:3306 --name mariadb -e MARIADB_USER=test -e MARIADB_PASSWORD=test -e MARIADB_ROOT_PASSWORD=test -e MARIADB_DATABASE=test mariadb:latest