let index = 0;
let imgindex = 0;
let repeatCount = 30;
var previousImage = null;
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
        randomY = (allimages[imgindex] !== "elephant") ? Math.floor(Math.random() * 53) + 35 : Math.floor(Math.random() * 40 + 30);
      }
      else{
        img.id = "balloon" + index + "";
        randomY = Math.floor(Math.random() * 20);
        balloons.push(img);
      }
      randomX = Math.floor(Math.random() * 90);
      img.style.left = randomX + "%";
      img.style.top = randomY + "%";
      img.width = (allimages[imgindex] !== "elephant") ? "100" : "250";
      previousImage = img;
      document.body.appendChild(img);
			resolve(index); // 画像の読み込みが成功した場合
		};
	
		img.onerror = () => {
      previousImage.width = (allimages[imgindex] !== "elephant") ? "150" : "275";
      previousImage.style.left = Math.floor(Math.random() * 40) + 20 + "%"; 
      previousImage.style.top = (allimages[imgindex] !== "balloon") ? "50%" : "10%";
      document.body.appendChild(previousImage);
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
}


function moveImage() {
  let leftArray = balloons.map(item => ((item.offsetLeft / window.innerWidth) * 100));
  let modifiedArray = leftArray.map(item => item + 0.05);
  const indexArrayGreater = modifiedArray.map((item, index) => item >= 91 ? index : -1).filter(index => index !== -1);
  balloons.forEach((balloon, index) => {
    balloon.style.left = modifiedArray[index] + "%";
  });
  if(indexArrayGreater.length > 0){
    for(let index of indexArrayGreater){
      balloons[index].style.left = "0%";
    }
  }
  requestAnimationFrame(moveImage)
}

loadImages();
requestAnimationFrame(moveImage);