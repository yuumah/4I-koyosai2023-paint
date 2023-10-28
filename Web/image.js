let index = 0;
let imgindex = 0;
let repeatCount = 30;
let previousImage = null;
let balloons = [];
let allimages = ["flower", "balloon", "turtle", "butterfly", "elephant"];
let randomX = 0;
let randomY = 0;

function loadImage(index) {
	return new Promise((resolve, reject) => {
		let img = document.createElement("img");
		img.className = allimages[imgindex];
		img.src = "http://tk2-233-26371.vs.sakura.ne.jp:7000/images?type="+ allimages[imgindex] +"&index=" + index;
		img.onload = () => {
      if(allimages[imgindex] !== "balloon"){
        randomY = Math.floor(Math.random() * 50) + 35;
      }
      else{
        img.id = "balloon" + index + "";
        randomY = Math.floor(Math.random() * 20);
        balloons.push(img);
      }
      img.style.left = Math.floor(Math.random() * 91) + "%";
      img.style.top = randomY + "%";
      img.width = "100";
      previousImage = img;
      document.body.appendChild(img);
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
      if (imgindex < allimages.length - 1) {
        imgindex++;
        index = 0;
        await loadImage(index);
      }
      else {
        break;
      }
    }
    index++;
  }

  moveImage();
}


function moveImage() {
  let leftArray = balloons.map(item => (item.offsetLeft / window.innerWidth) * 100);
  let modifiedArray = leftArray.map(item => item + 0.3);
  const indexArrayGreaterThan93 = modifiedArray.map((item, index) => item >= 91 ? index : -1).filter(index => index !== -1);
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

setTimeout(loadImages, 100);
