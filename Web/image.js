var repeatCount = 5;
var index = 0;

//画像更新対応ver(flower)
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
		document.body.appendChild(img); // 画像を表示
		resolve(index); // 画像の読み込みが成功した場合
	};

	img.onerror = () => {
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
		break; // エラーが発生したらループを中断
	}
	index++;
}
}

loadImages();

//自己増幅ver(balloon)
for (let i = 0; i < repeatCount; i++) {
    let img = document.createElement("img");
    img.className = "ballon";
    img.src = "http://tk2-233-26371.vs.sakura.ne.jp:7000/images?type=balloon&index=0";
    img.width = "100";
    document.body.appendChild(img);
}

let randomImage = document.getElementsByClassName("ballon");

for (let i = 0; i < randomImage.length; i++) {
    let randomX = Math.floor(Math.random() * 95); 
    let randomY = Math.floor(Math.random() * 20); 
    randomImage2[i].style.left = randomX + "%";
    randomImage2[i].style.top = randomY + "%";
}
