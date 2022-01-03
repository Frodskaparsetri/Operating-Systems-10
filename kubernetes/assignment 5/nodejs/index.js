const express = require('express')
const app = express()
const port = 3000;


app.get('/', (req, res) => {
    res.send('Hello World 2.0!');
});

app.get('/:name', (req, res) => {
    const name = req.params.name;
    res.send(`Hello ${name} 2.0!`);
});

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
});