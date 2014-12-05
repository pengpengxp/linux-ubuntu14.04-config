function getTimec()
{
								//获取时间的值
								var zeroDate = new Date(0);
								print("new Date(0)=");
								print(zeroDate);
								zeroDate-=zeroDate.getMilliseconds();
								print(zeroDate);
								var nowDate = new Date();
								print("new Date()=");
								print(nowDate);
								nowDate-=nowDate.getMilliseconds();
								print("nowDate-=nowDate.getMilliseconds();nowDate=");
								print(nowDate);
								zeroDate/=1000;
								print("zeroDate/=1000;zeroDate=");
								print(zeroDate);
								nowDate/=1000;
								print("nowDate/=1000;nowDate=");
								print(nowDate);
								var tDate = nowDate - zeroDate;
								print("nowDate - zeroDate=");
								print(tDate);
								//时间初处理Timec为结果
								var Timec = tDate;
								Timec *= 1717986919;
								Timec /= 4294967296;
								Timec=Math.floor(Timec);
								Timec /= 2;
								Timec=Math.floor(Timec);
								print(Timec);
								var peng=(Timec & 0xFF);
								print(peng);
								var xie=(Timec & 0xFF00)/0x100;
								print(xie);
								var e=(Timec & 0xFF0000)/0x10000;
								print(e);
								var w=(Timec & 0xFF000000)/0x1000000;
								print(w);
								return Timec;
}
function peng()
{
	var t=0x1234;
	print(t);
	var s=(t & 0xFF);
	print(s);
	var k=(t & 0xFF00)/0x100;
	print(k);
}
