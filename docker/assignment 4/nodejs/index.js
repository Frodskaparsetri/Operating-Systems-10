const express = require('express');
const mariadb = require('mariadb');

const pool = mariadb.createPool({
  host: "db", 
  user:'test', 
  port:3306,
  database: 'test',
  password: 'test',
  connectionLimit: 10
});


const app = express()
const port = 3000;


app.get('/', (req, res) => {
    res.send('Hello World!');
});

app.get("/random", async (req, res) => {
  let connection;

  try {
    const name = req.params.name;
    const connection = await pool.getConnection();
    const rows = await connection.query("SELECT name FROM names ORDER BY RAND() LIMIT 1");

    res.send(`Hello ${rows[0]?.name}`);

    await connection.end();
  } catch(e) {
    res.send(`Failed to read random name! ${e}`);

    if(connection) {
      await connection.end();
    }
  }
}); 

app.get('/add/:name', async (req, res) => {
  
  let connection;

  try {
    const name = req.params.name;
    connection = await pool.getConnection();
    await connection.query(`INSERT INTO names (name) VALUES ('${name}')`);

    res.send(`Name added!`);

    await connection.end();
  } catch(e) {
    res.send(`Failed to add! ${e}`);
    if(connection) {
      await connection.end();
    }
  }
});

app.listen(port, () => {
  console.log(`Example appasdasd listening at http://localhost:${port}`)
});