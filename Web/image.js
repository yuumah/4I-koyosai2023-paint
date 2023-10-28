let index = 0;
let repeatCount = 30;
let previousImage = null;
let balloons = [];

function loadImage(index) {
	return new Promise((resolve, reject) => {
		let img = document.createElement("img");
		img.className = "flower";
		img.src = "http://tk2-233-26371.vs.sakura.ne.jp:7000/images?type=flower&index=" + index;
	
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
			reject(index); // 画像の読み込みが失敗した場合
		};
	});
}

async function loadImages() {
  while (true) {
    try {
      await loadImage(index);
    } catch (errorIndex) {
      break;
    }
    index++;
  }

  moveImage();
}

function moveImage() {

  let leftArray = balloons.map(item => (item.offsetLeft / window.innerWidth) * 100);
  let modifiedArray = leftArray.map(item => item + 0.3);
  const indexArrayGreaterThan93 = modifiedArray.map((item, index) => item >= 93 ? index : -1).filter(index => index !== -1);
  balloons.forEach((balloon, index) => {
    balloon.style.left = modifiedArray[index] + "%";
  });
  if(indexArrayGreaterThan93.length > 0){
    for(const index of indexArrayGreaterThan93){
      balloons[index].style.left = "0%";
    }
  }
  setTimeout(moveImage, 50);
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
  balloons.push(img);
}

setTimeout(loadImages, 50);
