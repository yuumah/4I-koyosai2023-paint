const fs = require("fs");
const express = require("express");
const bodyParser = require("body-parser");
const glob = require("glob");

const PORT = process.env.PORT || 7000;
const app = express();
app.use(bodyParser.urlencoded({ limit: "8mb", extended: true }));
app.use(bodyParser.json());

const token = require("./token.json").token;
const image_types = ["flower", "butterfly"];

app.get("/", (req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });
  res.end("OK");
});


// 画像の取得
app.get("/images", (req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });
  if(req.query.token !== token){
    res.end("query parameter is invalid");
    return;
  }
  const type = req.query.type;
  let is_valid = false;
  image_types.forEach((t) => {
    if(t === type) is_valid = true;
  });
  if(!is_valid){
    res.end("type is invalid");
    return;
  }
  const images = glob.sync(`images/${type}/*.png`);
  let encoded_images = [];
  images.forEach((image) => {
    const data = fs.readFileSync(image);
    encoded_images.push(data.toString("base64"));
  });
  res.end(JSON.stringify(encoded_images));
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
