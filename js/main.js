function setWidth(Width)
{
	document.getElementById("wrap").style.width = Width;
	var a = new Date();
	a = new Date(a.getTime() +1000*60*60*24*365);
	document.cookie = 'SiteWidth='+Width+'; expires='+a.toGMTString()+';';
}