window.onload = function(){
	var canvas = document.getElementById("snowy");
	var ctx = canvas.getContext("2d");
	
	var W = window.innerWidth;
	var H = window.innerHeight;
	canvas.width = W;
	canvas.height = H;
	
	var maxParts = 35; 
	var particles = [];
	for(var i = 0; i < maxParts; i++)
	{
		particles.push({
			x: Math.random()*W, 
			y: Math.random()*H, 
            r: Math.random()*10, 
			d: Math.random()*maxParts 
		})
	}
	
	function draw()
	{
		ctx.clearRect(0, 0, W, H);
		
		ctx.fillStyle = "orange";
		ctx.beginPath();
		for(var i = 0; i < maxParts; i++)
		{
			var p = particles[i];
			ctx.moveTo(p.x, p.y);
			ctx.arc(p.x, p.y, p.r, Math.PI, Math.PI*2, true);
		}
		ctx.fill();
        update();
	}
	
	var ang = 0;
	function update()
	{
		ang += Math.random() * (0.01) + (0.05) ;
		for(var i = 0; i < maxParts; i++)
		{
			var p = particles[i];
            p.y += Math.cos(ang+p.d) + 1 + p.r/2;
			p.x += 0.2*Math.sin(ang + i) * 12;
			
			if(p.x > W+5 || p.x < -5 || p.y > H)
			{
				if(i%3 > 0) 
				{
					particles[i] = {x: Math.random()*W, y: -10, r: p.r, d: p.d};
				}
				else
				{
					if(Math.sin(ang) > 0)
					{
						particles[i] = {x: -5, y: Math.random()*H, r: p.r, d: p.d};
					}
					else
					{
						particles[i] = {x: W+5, y: Math.random()*H, r: p.r, d: p.d};
					}
				}
			}
		}
	}
	
	setInterval(draw, 33);
}





