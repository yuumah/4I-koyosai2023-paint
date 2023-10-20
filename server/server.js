const fs = require("fs");
const express = require("express");
const bodyParser = require("body-parser");

const PORT = process.env.PORT || 7000;
const app = express();
app.use(bodyParser.urlencoded({ extended: true }));

app.get("/", (req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });
  res.end("OK");
});

app.listen(PORT);
console.log(`Server running at ${PORT}`);
