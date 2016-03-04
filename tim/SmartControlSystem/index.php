<!DOCTYPE html>
<html lang="zh-CN">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Smart Control System</title>
	<head>
		<script src="http://libs.baidu.com/jquery/2.0.0/jquery.min.js"></script>
		<script src="http://libs.baidu.com/bootstrap/3.0.3/js/bootstrap.min.js"></script>
		<link href="http://libs.baidu.com/bootstrap/3.0.3/css/bootstrap.min.css" rel="stylesheet">
		<script type="text/javascript">
		function light(state)
		{
			xmlhttp=new XMLHttpRequest();
			xmlhttp.open("GET","/control.php?pin="+$("#io").val()+"&state="+state,true);
			xmlhttp.onreadystatechange=function()
			{
			  if (xmlhttp.readyState==4)
				if(xmlhttp.status==200)$("#returndata").html(xmlhttp.responseText);
			}
			xmlhttp.send();
		}</script>
	</head>
	<body>
		<div class="col-md-6" style="margin: 20px;">
			<label for="io">PIN</label><br>
			<input class="form-control" id="io" value="1"><br>
			<label for="digital">DIGITAL(0/1)</label><br>
			<input class="form-control" id="digital" value="1"><br>
			<label for="analog">ANALOG(0~255)</label><br>
			<input class="form-control" id="analog" value="1"><br>
			<button class="btn btn-success btn-lg btn-block" type="button" onclick="light(1)">ON</button><br>
			<button class="btn btn-success btn-lg btn-block" type="button" onclick="light(0)">OFF</button><br>
			<div id="returndata"></div>
		</div>
	</body>
</html>
