const fs = require("fs");
const express = require("express");
const bodyParser = require("body-parser");
const glob = require("glob");
const base64 = require('urlsafe-base64');

const PORT = process.env.PORT || 7000;
const app = express();
app.use(bodyParser.urlencoded({ limit: "8mb", extended: true }));
app.use(bodyParser.json());

const token = require("./token.json").token;
const image_types = glob.sync("images/*").map((path) => {
  return path.substring(path.indexOf("/")+1);
});

app.get("/", (req, res) => {
  res.writeHead(200, { "Content-Type": "text/html" });
  res.end("OK");
});


// 画像の取得
app.get("/images", (req, res) => {
  const index = Number(req.query.index);
  const type = req.query.type;
  let is_valid = false;
  image_types.forEach((t) => {
    if(t === type) is_valid = true;
  });
  if(!is_valid || isNaN(index)){
    res.writeHead(200, { "Content-Type": "text/html" });
    res.end("query parameter is invalid");
    return;
  }
  const images = glob.sync(`images/${type}/*.png`);
  if(index < 0 || index >= images.length){
    res.writeHead(200, { "Content-Type": "text/html" });
    res.end("index out of range");
    return;
  }
  res.writeHead(200, { "Content-Type": "image/png" });
  const images_info = images.map((img) => {
    return {
      image: img,
      time: fs.statSync(img).mtime,
    };
  }).sort((a, b) => a.time - b.time);
  const image = images_info[index].image;
  res.end(fs.readFileSync(image));
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
  const Crypto = require("crypto");
  const buff = Crypto.randomBytes(16);
  const hex = buff.toString("hex");
  if(req.query.token !== token){
    res.end("query parameter is invalid");
    return;
  }
  let img_type = req.body.type;
  let decoded_image = base64.decode( req.body.image );
  fs.writeFile(`./images/${img_type}/image_${hex}.png`, decoded_image, function (err) {
    console.log(err);
  });

  console.log(req.files);
  console.log(req.body);
  console.log(req.query);
  res.end("OK");
});

app.listen(PORT);
console.log(`Server running at ${PORT}`);
