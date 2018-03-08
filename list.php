<?php 
 require_once "shared.php";
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="language" content="en" />

        <!-- blueprint CSS framework -->
        <link rel="stylesheet" type="text/css" href="css/screen.css" media="screen, projection" />
        <link rel="stylesheet" type="text/css" href="css/print.css" media="print" />
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Oxygen:400,300,700" />
        <link rel="stylesheet" type="text/css" href="css/main.css" />
        <link rel="stylesheet" type="text/css" href="css/form.css" />
        <!--<link rel="stylesheet" href="css/select2.css" />-->

        <link rel="icon" type="image/png" href="image/iconunibba.png">
        <link rel="stylesheet" type="text/css" href="css/jquery-ui.css" />
		<!--<link rel="stylesheet" type="text/css" href="css/jqueryslidemenu.css" />-->
		<script type="text/javascript" src="js/jquery.js"></script>
		<script type="text/javascript" src="js/jquery-ui.min.js"></script>
		<!--<script type="text/javascript" src="js/jqueryslidemenu.js"></script>-->
		
		<style type="text/css">
	      @import "datatables/media/css/demo_page.css";
	      @import "datatables/media/css/demo_table.css";
          .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 2px; }		  
        </style>
		
		<script type="text/javascript" src="datatables/media/js/jquery.dataTables.js"></script>
		
		<title>Pendataan Ulang Mahasiswa UNIBBA</title>
    </head>
<body>
<script type="text/javascript">
    $(document).ready(function () {

	  
	  oTable1=$("#lst_stat_uns").dataTable({"bFilter": false,
									"bSort": false,
									"bPaginate": false,
									"bInfo": false});
									
      oTable2=$("#lst_stat_uns1").dataTable({"bFilter": false,
									"bSort": false,
									"bPaginate": false,
									"bInfo": false});
	  oTable3=$("#lst_stat_uns2").dataTable({"bFilter": false,
									"bSort": false,
									"bPaginate": false,
									"bInfo": false});								
	 oTable4=$("#lst_stat_uns3").dataTable({"bFilter": false,
									"bSort": false,
									"bPaginate": false,
									"bInfo": false});
     oTable5=$("#lst_stat_uns4").dataTable({"bFilter": false,
									"bSort": false,
									"bPaginate": false,
									"bInfo": false});									
	 oTable6=$("#lst_stat_uns5").dataTable({"bFilter": false,
									"bSort": false,
									"bPaginate": false,
									"bInfo": false});									
   });
</script>


<div id="header">
<a href="index.php"><img src="image/header3.png" height="110" width="1000"></a>
</div><!-- header -->

<div id="wrapper" style="margin-top: -20px;">
<div id="content">
	
<!-- <h1>Daftar Mahasiswa yang terdaftar</h1> -->

<div class="form">


<?php
	$vwstat = new vw_stat; 
	echo $vwstat->summary_stat_mng();
?>

</div><!-- form -->
</div><!-- content -->
<div class="clear"></div>
</div><!-- wrapper -->

<div id="footer">
<p>
Jalan RAA. Wiranatakusuman No. 7 Bale Endah Bandung <br>
Telepon (022) 594 0443, 594 0262, 594 7087 <br>
Fax (022) 594 0443 <br>
Situs <a href="http://www.unibba.ac.id/">www.unibba.ac.id</a> <br><br>

© PUMHS Pendataan Ulang Mahasiswa 2013 <br>
<!--Copyright &copy; 2013 by FTI Unibba<br/>
All Rights Reserved.<br/>
-->

</p>
</div><!-- footer -->
</div><!-- page -->

<!--<div id="ui-datepicker-div" class="ui-datepicker ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"></div>
<script src="js/spops-2.js" charset="UTF-8" type="text/javascript"></script>
<iframe src="js/pquery-0.htm" style="display: none;"></iframe>-->
</body>
</html>
