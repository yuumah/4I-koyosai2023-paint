const fs = require("fs");
const express = require("express");
const bodyParser = require("body-parser");

const PORT = process.env.PORT || 7000;
const app = express();
app.use(bodyParser.urlencoded({ limit: "8mb", extended: true }));
app.use(bodyParser.json());

const token = require("./token.json").token;

app.get("/", (req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });
  res.end("OK");
});

app.get("/uploadImages", (req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });
  if(req.query.token !== token){
    res.end("query parameter is invalid");
    return;
  }
  res.end("get uploadImages");
});

app.post("/uploadImages", (req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });

  if(req.query.token !== token){
    res.end("query parameter is invalid");
    return;
  }

  console.log(req.files);
  console.log(req.body);
  console.log(req.query);

  res.end("OK");
});

app.listen(PORT);
console.log(`Server running at ${PORT}`);