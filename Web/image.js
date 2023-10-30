let index = 0;
let imgindex = 0;
let repeatCount = 30;
let previousImage = null;
let balloons = [];
let endimages = [];
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
        randomY = Math.floor(Math.random() * 60) + 25;
      }
      else{
        img.id = "balloon" + index + "";
        randomY = Math.floor(Math.random() * 20);
        balloons.push(img);
      }
      randomX = (allimages[imgindex] !== "elephant") ? Math.floor(Math.random() * 90) : Math.floor(Math.random() * 80);
      img.style.left = randomX + "%";
      img.style.top = randomY + "%";
      img.width = (allimages[imgindex] !== "elephant") ? "100" : "250";
      previousImage = img;
      if (endimages.length > 3) endimages.shift();
      endimages.push(img); 
      document.body.appendChild(img);
			resolve(index); // 画像の読み込みが成功した場合
		};
	
		img.onerror = () => {
      if (endimages.length > 0 && endimages) {
        for(const endimage of endimages){
          endimage.width = (allimages[imgindex] !== "elephant") ? "150" : "275";
        }
        endimages = [];
      }
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
        allimages = 0;
        break;
      }
    }
    index++;
  }
}

function moveImage() {
  let leftArray = balloons.map((item) => (item.offsetLeft / window.innerWidth) * 100);
  let modifiedArray = leftArray.map((item) => item + 0.05);
  const indexArrayGreater = modifiedArray
    .map((item, index) => (item >= 95 ? index : -1))
    .filter((index) => index !== -1);

  balloons.forEach((balloon, index) => {
    balloon.style.left = modifiedArray[index] + "%";
  });

  if (indexArrayGreater.length > 0) {
    for (let index of indexArrayGreater) {
      balloons[index].style.left = "0%";
    }
  }
  requestAnimationFrame(moveImage);
}
loadImages();
requestAnimationFrame(moveImage);