<?php

 session_start();

 error_reporting(E_ALL & ~E_WARNING);
 
 $server = $_SERVER['DOCUMENT_ROOT'];
 $base_path = $server . '/admin_app/';
 if(!is_dir($base_path)){
   if($server=="/home/uni10000/public_html/pumhs") {
        $base_path = $server . '/admin_app/';		
	} 
    else{
	  $base_path = $server . '/admin_app/';	 
	}  
 }
 
 require_once $base_path."view/vw_stat.class.inc";
 require_once $base_path."dt/dt_admin.class.inc";
 
 $username = isset($_SESSION["userName"]) ? $_SESSION["userName"] : ''; 
 $password = isset($_SESSION["password"]) ? $_SESSION["password"]: ''; 
 
 $dt=new dt_admin;
 
 $where   = "user='".$username."'and pass='".$password."'";
 $hasil = $dt->getData($where);
 
if ($dt->numrows==0){
  ?>
    <script>
	    window.location="index.php";
	</script>
  <?php
}
 
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="language" content="en" />

        <!-- blueprint CSS framework -->
        <link rel="stylesheet" type="text/css" href="../css/screen.css" media="screen, projection" />
        <link rel="stylesheet" type="text/css" href="../css/print.css" media="print" />
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="../css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Oxygen:400,300,700" />
        <link rel="stylesheet" type="text/css" href="../css/main.css" />
        <link rel="stylesheet" type="text/css" href="../css/form.css" />
        <!--<link rel="stylesheet" href="css/select2.css" />-->

        <link rel="icon" type="image/png" href="../image/iconunibba.png">
       <!-- <link rel="stylesheet" type="text/css" href="../../css/jquery-ui.css" />
		<link rel="stylesheet" type="text/css" href="css/jqueryslidemenu.css" />
		<script type="text/javascript" src="../../js/jquery.js"></script>
		<script type="text/javascript" src="../../js/jquery-ui.min.js"></script>-->
		
		<script type="text/javascript" src="../js1/jquery-1.8.0.min.js"></script>
	    <script type="text/javascript" src="../js1/jquery-ui-1.8.23.custom.min.js"></script>
		
		<link type="text/css" href="../css1/jquery-ui-1.8.23.custom.css" rel="stylesheet" />
		<!--<script type="text/javascript" src="js/jqueryslidemenu.js"></script>-->
		
		<style type="text/css">
	      @import "../datatables/media/css/demo_page.css";
	      @import "../datatables/media/css/demo_table.css";
          .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 10px; }	  
        </style>
		
		<link rel="stylesheet" type="text/css" href="../css1/menu.css" />
		
		<script type="text/javascript" src="../datatables/media/js/jquery.dataTables.js"></script>
		
		<title>Pendataan Ulang Mahasiswa UNIBBA</title>
    </head>
<body>
<script type="text/javascript">
    $(document).ready(function () {
	  $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=1",
									 success : function(data){
					                            $("#data").html(data);												
										        
				  oTable=$("#lst_mhs").dataTable({"bFilter": false,
												"bSort": false,
												"bPaginate": false,
												"bInfo": false,
												"fnDrawCallback": function ( oSettings ) {
													if ( oSettings.aiDisplay.length == 0 )
													{
														return;
													}
													 
													var nTrs = $('#lst_mhs tbody tr');
													var iColspan = nTrs[0].getElementsByTagName('td').length;
													var sLastGroup = "";
													for ( var i=0 ; i<nTrs.length ; i++ )
													{
														var iDisplayIndex = oSettings._iDisplayStart + i;
														var sGroup = oSettings.aoData[ oSettings.aiDisplay[iDisplayIndex] ]._aData[0];
														if ( sGroup != sLastGroup )
														{
															var nGroup = document.createElement( 'tr' );
															var nCell = document.createElement( 'td' );
															nCell.colSpan = iColspan;
															nCell.className = "group";
															nCell.innerHTML = sGroup;
															nGroup.appendChild( nCell );
															nTrs[i].parentNode.insertBefore( nGroup, nTrs[i] );
															sLastGroup = sGroup;
														}
													}
												},
												"aoColumnDefs": [
													{ "bVisible": false, "aTargets": [ 0 ] },
													{
														"fnRender": function ( oObj, sVal ) {
															return  sVal;
														},
														"aTargets": [ 0 ]
													}
												],
												"aaSortingFixed": [[ 0, 'asc' ]],
												"aaSorting": [[ 1, 'asc' ]],
												"sDom": 'lfr<"giveHeight"t>ip',
												 "oLanguage": {
												 "sSearch": "Search all columns:"
												}});
				  
				  oTable1=$("#tb_login").dataTable({"aaSorting": []});
				  oTable1=$("#tb_create").dataTable({"aaSorting": []});
				  oTable1=$("#tb_update").dataTable({"aaSorting": []});
				  oTable1=$("#lst_stat_uns").dataTable({"bFilter": false,
												"bSort": false,
												"bPaginate": false,
												"bInfo": false});

				                               }
                                  });
   });
   function changecontent(idx)
   {
     $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	 $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx="+idx,
									 success : function(data){
					                            $("#data").html(data);						
												  $( "#tabs" ).tabs();
												  $( "#tabs2" ).tabs();
												  $( "#tabs3" ).tabs();
												  oTable4=$("#lst_stat").dataTable();
												  oTable5=$("#lst_krs").dataTable();
												  oTable6=$("#lst_sbrnmtk").dataTable();
												  $(".display_entry").dataTable({"aaSorting": []});	
												  oTable1=$(".display_ver").dataTable({"aaSorting": []});
												  oTable1=$("#logctk").dataTable({"aaSorting": []});
												  oTable1=$("#logmhs").dataTable({"aaSorting": []});
												  oTable2=$("#logopt").dataTable({"aaSorting": []});
												  oTable3=$("#logadmin").dataTable({"aaSorting": []});
												    
												  }
				                               
                                  });
   }
   
   
   function filter_list_mhs(kd_fak)
   {
      $("#data_list_mhs").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var prodi = $("#Prodi_hsl_val").val();	
       var thn = $("#thn_hsl_val").val();
	   var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=3&prodi="+prodi+"&thn="+thn+"&fak="+fak,
									 success : function(data){
					                            $("#data_list_mhs").html(data);												
										        $( "#tabs" ).tabs();
												oTable1=$(".display_entry").dataTable({"aaSorting": []});
				                               }
                                  });
   
   }
   
   function filter_verifikasi(kd_fak,idx)
   {
      switch(idx){
      case 1:
	  var prodi = $("#Prodi_hsl_val").val();	
      var thn = $("#thn_hsl_val").val();
	  var fak = kd_fak;	  
	  $("#data_blm_lyk").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  break;
      case 2:
      var prodi = $("#Prodi_frm_ver").val();	
      var thn = $("#thn_frm_ver").val();
	  var fak = kd_fak;	  
      $("#data_lyk").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");      
      break;
	  case 3:
	  var prodi = $("#Prodi_hsl_ver").val();	
      var thn = $("#thn_hsl_ver").val();
	  var fak = kd_fak;
	  $("#data_lls").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  break;
	  case 4:
	  var prodi = $("#Prodi_tlls").val();	
      var thn = $("#thn_tlls").val();
	  var fak = kd_fak;
	  $("#data_tlls").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  break;
	  case 5:
	  var nmfile = $("#nmfile").val();	
      //var thn = $("#thn_sdver").val();
	  var fak = kd_fak;
	  $("#data_sdver").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  break;
	 } 
	  
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=6&prodi="+prodi+"&thn="+thn+"&fak="+fak+"&nmfile="+nmfile+"&idx1="+idx,
									 success : function(data){
					                           
     											switch(idx){
												 case 1 : $("#data_blm_lyk").html(data);
												          $("#lst_mhs1").dataTable({"aaSorting": []});
												          break;
                                                 case 2 : $("#data_lyk").html(data);
												          $("#lst_mhs2").dataTable({"aaSorting": []});
												          break;
                                                 case 3 : $("#data_lls").html(data);
												          $("#lst_mhs3").dataTable({"aaSorting": []});
														  break;
												  
                                                 case 4 : $("#data_tlls").html(data);
												          $("#lst_mhs4").dataTable({"aaSorting": []});
												          break;
                                                 case 5 : $("#data_sdver").html(data);
												          oTable2=$("#lst_mhs5").dataTable({"aaSorting": []});
												          break;														  
												}
										        //oTable2=$(".display_ver").dataTable({"aaSorting": []});
				                               }
                                  });
   
   }
   
   function filter_perwalian(kd_fak)
   {
      $("#data_absperwalian").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_absperwalian").val();	
	   var prodi = $("#Prodi_absperwalian").val();	
       var thn = $("#thn_absperwalian").val();
	   var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=9&prodi="+prodi+"&thn="+thn+"&fak="+fak+"&idx1=6&sem="+sem,
									 success : function(data){
					                            $("#data_absperwalian").html(data);
												oTable4=$("#lst_stat").dataTable();
										        $( "#tabs" ).tabs();												
				                               }
                                  });
   
   }
   
   function filter_krs(kd_fak)
   {
      $("#data_krs").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_krs").val();	
	   var prodi = $("#Prodi_krs").val();	
       var thn = $("#thn_krs").val();
	   var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=9&prodi="+prodi+"&thn="+thn+"&fak="+fak+"&idx1=7&sem="+sem,
									 success : function(data){
					                            $("#data_krs").html(data);
												oTable4=$("#lst_krs").dataTable();
										        $( "#tabs3" ).tabs();												
				                               }
                                  });
   
   }
   function filter_sbrnmtk(kd_fak)
   {
       $("#data_sbrnmtk").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_sbrnmtk").val();	
	   var prodi = $("#Prodi_sbrnmtk").val();	
       var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=9&prodi="+prodi+"&thn=0&fak="+fak+"&idx1=8&sem="+sem,
									 success : function(data){
					                            $("#data_sbrnmtk").html(data);
												oTable4=$("#lst_sbrnmtk").dataTable();
										        $( "#tabs3" ).tabs();												
				                               }
                                  });
   
   }
   
   
   function ch_cont_tab_fak(idx){
	    $("#data"+(idx)).html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='image/ajax-loader.gif' /></div>");
		
	  
	     
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx="+(idx+1),
									 success : function(data){												
												$("#data"+(idx)).html(data);
												if(idx==5){
												  oTable1=$("#tb_login").dataTable({"aaSorting": []});
				                                  oTable2=$("#tb_create").dataTable({"aaSorting": []});
				                                  oTable3=$("#tb_update").dataTable({"aaSorting": []});
												 }else{
												 
												 $(".display").dataTable({"aaSorting": []});
												 }
												  
				                               }
                                  }); 
	   
	   
   }
   
   
   
   function rekap_prodi(kd_prodi)
   {
      $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=10&kd_prodi="+kd_prodi,
									 success : function(data){
					                            $("#data").html(data);												
										        $( "#tabs" ).tabs();
												$( "#tabs2" ).tabs();
												$(".display_ver").dataTable({"aaSorting": []});												
												oTable1=$('#lst_stat').dataTable();	
				                               }
                                  });
   
   }
   
   function dtmhs(idx,noktp)
   {
     $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	 $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx="+idx+"&noktp="+noktp,
									 success : function(data){					                            
												
															$("#data").html(data);
															//$( "#tabs" ).tabs();
														  												
				                               }
                                  });
   }
   
   function logout()
   {
       $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=7",
									 success : function(data){
												window.location="index.php";
				                               }
                                  }); 
		
		
   }
   function cetak_statistik(idx)
   {
       $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	 switch(idx)
     {	 
	  case 1 : $.ajax({
                                     type : "POST",
				                     url : "ctk_pdf.php",
				                     cache: false,
				                     data :"idx=1",
									 success : function(data){
												changecontent(12);
												window.open(data,'Download'); 												
				                               }
                                  }); break;
								  
	 case 2 : $.ajax({
                                     type : "POST",
				                     url : "ctk_excel.php",
				                     cache: false,
				                     data :"idx=1",
									 success : function(data){
												changecontent(12);
												window.open(data,'Download'); 												
				                               }
                                  }); break;							  
		
	}	
   }
</script>


<div id="header">
<a href="index.php"><img src="../image/header3.png" height="110" width="1000"></a>
</div><!-- header -->

<div id="wrapper" style="margin-top: -20px;">
<div id="content">
	
<!-- <h1>Daftar Mahasiswa yang terdaftar</h1> -->

<div class="form">
<ul id="menu">
<li><a href="list.php">Home</a></li>
<li><a href="javascript:changecontent(2);">List Data Mahasiswa</a></li>
<li><a href="javascript:changecontent(5);">Verifikasi</a></li>
<li><a href="javascript:changecontent(8);">Persiapan Perkuliahan</a></li>
<li><a href="javascript:changecontent(11);">Log</a></li>
<li><a href="javascript:changecontent(12);">Cetak</a></li>
<li><a href="javascript:logout();">Logout</a></li>
</ul> 

<div  id='data'> </div>

<div id="dialog" title="Data Mahasiswa">
  <div id='frm'></div>
</div>  

</div>
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
