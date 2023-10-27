let index = 0;
let repeatCount = 5;
let previousImage = null;

function loadImage(index) {
	return new Promise((resolve, reject) => {
		let img = document.createElement("img");
		img.className = "flower";
		img.src = "http://tk2-233-26371.vs.sakura.ne.jp:7000/images?type=flower&index=" + index + "";
	
		img.onload = () => {
			let randomX = Math.floor(Math.random() * 95);  
			let randomY = Math.floor(Math.random() * 50) + 35; 
			img.style.left = randomX + "%";
			img.style.top = randomY + "%";
      img.width = "100";
			document.body.appendChild(img); // 画像を表示
      previousImage = img;
			resolve(index); // 画像の読み込みが成功した場合
		};
	
		img.onerror = () => {
      previousImage.width = "150";
      document.body.appendChild(previousImage); // 画像を表示
			reject(index); // 画像の読み込みが失敗した場合
		};
	});
}

async function loadImages() {
  while (true) {
    try {
      await loadImage(index);
    } catch (errorIndex) {
      console.log("画像の読み込みに失敗しました：" + errorIndex);
      break;
    }
    index++;
  }

  moveImage();
}

function moveImage() {
  let image = document.getElementById("balloon" + index + "");
  if (!image) {
    index = 0;
    image = document.getElementById("balloon" + index + "");
  }

  let positionX = (image.offsetLeft / window.innerWidth) * 100;
  positionX += 0.3;
  image.style.left = positionX + '%';

  if (positionX < 93) {
    index++;
    if (index >= repeatCount) {
      index = 0;
    }
    requestAnimationFrame(moveImage);
  }
  else {
    image.style.left = "0%";
    moveImage();
  }
}

for (let i = 0; i < repeatCount; i++) {
  let img = document.createElement("img");
  img.id = "balloon" + i + "";
  img.src = "http://tk2-233-26371.vs.sakura.ne.jp:7000/images?type=balloon&index=0";
  img.width = "100";
  let randomX = Math.floor(Math.random() * 95);
  let randomY = Math.floor(Math.random() * 20);
  img.style.left = randomX + "%";
  img.style.top = randomY + "%";
  document.body.appendChild(img);
}

loadImages();
