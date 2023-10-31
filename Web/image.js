let index = 0;
let imgindex = 0;
let balloons = [];
let endimages = [];
let animal_poses = [];
const allimages = ["flower", "balloon", "turtle", "butterfly", "elephant"];
const leave_dist = 20; // [px]

function isAnimal(imgindex) {
  return imgindex >= 2;
}

function calc_animal_min_dist(pos) {
  let min_dist = 1000000;
  animal_poses.forEach((p) => {
    const dist = (p.y-pos.y)*(p.y-pos.y) + (p.x-pos.x)*(p.x-pos.x)*3;
    if(min_dist > dist) min_dist = dist;
  });
  return Math.sqrt(min_dist);
}


function generate_random_pos() {
  // balloon or flower
  if (!isAnimal(imgindex)) {
    let randomY = 0;
    if (allimages[imgindex] !== "balloon") {
      randomY = Math.floor(Math.random() * 60) + 25;
    }
    else {
      randomY = randomY = Math.floor(Math.random() * 20);
    }
    const randomX = Math.floor(Math.random() * 90);
    return { y: randomY, x: randomX };
  }

  // 周りとの距離がleave_dist以上のものを適当に探す
  for (let i = 0; i < 100; i++) {
    const randomY = Math.floor(Math.random() * 60) + 25;
    const randomX = (allimages[imgindex] !== "elephant") ? Math.floor(Math.random() * 90) : Math.floor(Math.random() * 80);
    const pos = { y: randomY, x: randomX };
    const min_dist = calc_animal_min_dist(pos);
    if (min_dist >= leave_dist) {
      return pos;
    }
  }

  const randomY = Math.floor(Math.random() * 60) + 25;
  const randomX = (allimages[imgindex] !== "elephant") ? Math.floor(Math.random() * 90) : Math.floor(Math.random() * 80);
  return { y: randomY, x: randomX };
}


function loadImage(index) {
	return new Promise((resolve, reject) => {
		let img = document.createElement("img");
		img.className = allimages[imgindex];
		img.src = "http://tk2-233-26371.vs.sakura.ne.jp:7000/images?type="+ allimages[imgindex] +"&index=" + index;
		img.onload = () => {
      const random_pos = generate_random_pos();

      if (allimages[imgindex] === "balloon") {
        img.id = "balloon" + index;
        balloons.push(img);
      }

      if (isAnimal(imgindex)) animal_poses.push(random_pos);

      img.style.left = random_pos.x + "%";
      img.style.top = random_pos.y + "%";
      img.width = (allimages[imgindex] !== "elephant") ? "100" : "250";
      
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
        // allimages = 0;
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