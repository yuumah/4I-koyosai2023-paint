let i = 0; // endindexesのインデックス
let index = 0; // urlのインデックス
let imgindex = 0; // allimagesのインデックス
let balloons = [];
let endimages_fl = [], endimages_ba = [], endimages_tu = [], endimages_bu = [], endimages_el = [];
let endimages = [];
let endindexes = new Array(5).fill(-1);
let animal_poses = [];
const allimages = ["flower", "balloon", "turtle", "butterfly", "elephant"];
const leave_dist = 20; // [px]
const timeout = 2000; // [ms]

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
      randomY = Math.floor(Math.random() * 55) + 30;
    }
    else {
      randomY = randomY = Math.floor(Math.random() * 20);
    }
    const randomX = Math.floor(Math.random() * 90);
    return { y: randomY, x: randomX };
  }

  // 周りとの距離がleave_dist以上のものを適当に探す
  for (let i = 0; i < 100; i++) {
    const randomY = Math.floor(Math.random() * 50) + 30;
    const randomX = (allimages[imgindex] !== "elephant") ? Math.floor(Math.random() * 90) : Math.floor(Math.random() * 80);
    const pos = { y: randomY, x: randomX };
    const min_dist = calc_animal_min_dist(pos);
    if (min_dist >= leave_dist) {
      return pos;
    }
  }

  const randomY = Math.floor(Math.random() * 55) + 30;
  const randomX = (allimages[imgindex] !== "elephant") ? Math.floor(Math.random() * 90) : Math.floor(Math.random() * 80);
  return { y: randomY, x: randomX };
}

function width_border_change(imgindex) {
  if (endimages.length > 0){
    for(let endimage of endimages){
      endimage.width = "150";
      endimage.style.border = "solid 2px red";
    }
  }
}

function loadImage(index) {
	return new Promise((resolve, reject) => {
		let img = document.createElement("img");
		img.className = allimages[imgindex];
		img.src = "http://tk2-233-26371.vs.sakura.ne.jp:7000/images?type="+ allimages[imgindex] +"&index=" + index;
		img.onload = () => {
      console.log("onload" + imgindex, index)
      const random_pos = generate_random_pos();

      if (allimages[imgindex] === "balloon") {
        img.id = "balloon" + index;
        balloons.push(img);
      }

      if (isAnimal(imgindex)) animal_poses.push(random_pos);

      img.style.left = random_pos.x + "%";
      img.style.top = random_pos.y + "%";
      img.width = (allimages[imgindex] === "elephant") ? "200" : "100";

      if (endimages.length === 3){
        endimages[0].width = "100";
        endimages[0].style.border = "none";
        endimages.shift();
      }

      endimages.push(img);

      endindexes[imgindex] = index + 1;

      document.body.appendChild(img);
			resolve(index); // 画像の読み込みが成功した場合
		};
	
		img.onerror = () => {
      
      width_border_change(imgindex);

			reject(index); // 画像の読み込みが失敗した場合
		};
	});
}

async function loadImages() {
  while (true) {
    try {
      await loadImage(index);
    } catch (e) {
      if (imgindex < allimages.length - 1) {
        imgindex++;
        index = 0;
        await loadImage(index);
      }
      else {
        imgindex = 0;
        break;
      }
    }
    index++;
  }
  setInterval(() => {
    reload();
  }, 1000);
  requestAnimationFrame(moveImage);
}


async function reload() {
  i = 0;
  imgindex = 0;
  while (i < endindexes.length) {
    try {
      await loadImage(endindexes[i]);
    } catch {}
    if (imgindex < allimages.length - 1) imgindex++;
    i++;
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

