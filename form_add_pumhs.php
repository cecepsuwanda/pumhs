<?php
   require_once 'shared.php';
   
   $username = isset($_SESSION["username"]) ? $_SESSION["username"] : ''; 
   $nomorKTP = isset($_SESSION["nomorKTP"]) ? $_SESSION["nomorKTP"]: ''; 
   $password = isset($_SESSION["password"]) ? $_SESSION["password"]: '';   
   
	
?>

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="language" content="en" />

        <!-- blueprint CSS framework -->
        <link rel="stylesheet" type="text/css" href="css/screen.css" media="screen, projection" />
        <link rel="stylesheet" type="text/css" href="css/print.css" media="print" />
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="/beasiswa/css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Oxygen:400,300,700" />
        <link rel="stylesheet" type="text/css" href="css/main.css" />
        <link rel="stylesheet" type="text/css" href="css/form.css" />
        <link rel="stylesheet" href="css/select2.css" />

        <link rel="icon" type="image/png" href="image/iconunibba.png">
        <link rel="stylesheet" type="text/css" href="css/jquery-ui.css" />
		<link rel="stylesheet" type="text/css" href="css/jqueryslidemenu.css" />
		<script type="text/javascript" src="js/jquery.js"></script>
		<script type="text/javascript" src="js/jquery-ui.min.js"></script>
		<script type="text/javascript" src="js/jqueryslidemenu.js"></script>
		
		<style type="text/css">
	      @import "datatables/media/css/demo_page.css";
	      @import "datatables/media/css/demo_table.css";
          .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 12px; }		  
        </style>
		
		<script type="text/javascript" src="datatables/media/js/jquery.dataTables.js"></script>
		
		<title>Pendataan Ulang Mahasiswa UNIBBA</title>
    </head>
<body>
<?php
		
        
		
		//$username = $_SESSION["username"];
		//$nomorKTP = $_SESSION["nomorKTP"];
        //$password = $_SESSION["password"];

		
		
		
        $data = new dt_mhs;
        if ($data->KTPada($username)) {
                if ($password == $data->pass) {
					//data diambil dari tabel
					$prod = $data->prod; 
					$Nama_mahasiswa = $data -> Nama_mahasiswa;
					$jenisKelamin  = $data->jenisKelamin;
					$tanggalLahir  = $data->tanggalLahir;
					$tahunMasuk  = $data->tahunMasuk;
					$kelas = $data ->kelas;
					$nim  = $data->nim;
					$status  = $data->status;
					$tempatLahir  = $data->tempatLahir;
					$alamat  = $data->alamat;
					$kota  = $data->kota;
					$telepon  = $data->telepon;
					$provinsi  = $data->provinsi;
					$hp  = $data->hp;
					$kodePos  = $data->kodePos;
					$tanggalLulus  = $data->tanggalLulus;
					$tanggalMasuk  = $data->tanggalMasuk;
					$ipkAkhir  = $data->ipkAkhir;
					$nomorSkYudisium  = $data->nomorSkYudisium;
					$batasStudi  = $data->batasStudi;
					$tanggalYudisium  = $data->tanggalYudisium;
					$nomorSeriIjazah  = $data->nomorSeriIjazah;
					$smaAsal  = $data->smaAsal;
					$sksDiakui  = $data->sksDiakui;
					$namaTempatPekerjaan  = $data->namaTempatPekerjaan;
					$kodePekerjaan  = $data->kodePekerjaan;
					$prodiAsal  = $data ->prodiAsal;
					$universitasAsal  = $data->universitasAsal;
					$verifikasi = $data->verifikasi;
				}
				else {
					?>
						<script>
						//window.location="ilegal.html";
						</script>
					<?php
				}
		}
				else {
					?>
						<script>
						//window.location="ilegal.html";
						</script>
					<?php
				}		
			
?>

<script type="text/javascript">
          var jum=0
		  var tmp=0;
		  var is_edit=0;
	$(document).ready(function () {
	  $("#tabs").tabs();

      oTable2=$("#lst_krs").dataTable({
																	"fnDrawCallback": function ( oSettings ) {
																		if ( oSettings.aiDisplay.length == 0 )
																		{
																			return;
																		}
																		 
																		var nTrs = $('#lst_krs tbody tr');
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
																				return  "Semester "+sVal;
																			},
																			"aTargets": [ 0 ]
																		}
																	],
																	"bInfo": false,
																	"bPaginate": false,
																	"bFilter": false,
																	"aaSortingFixed": [[ 0, 'asc' ]],
																	"aaSorting": [[ 1, 'asc' ]],
																	"sDom": 'lfr<"giveHeight"t>ip',
																	 "oLanguage": {
																	 "sSearch": "Search all columns:"
																	}
																});
            oTable3=$("#lst_khs").dataTable({
																	"fnDrawCallback": function ( oSettings ) {
																		if ( oSettings.aiDisplay.length == 0 )
																		{
																			return;
																		}
																		 
																		var nTrs = $('#lst_khs tbody tr');
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
																	"bInfo": false,
																	"bPaginate": false,
																	"bFilter": false,
																	"aaSortingFixed": [[ 0, 'asc' ]],
																	"aaSorting": [[ 1, 'asc' ]],
																	"sDom": 'lfr<"giveHeight"t>ip',
																	 "oLanguage": {
																	 "sSearch": "Search all columns:"
																	}
																});

																
			<?php
			  if($verifikasi==1){
			?>													
			jum=parseInt(document.getElementById("jsks").value);													                  
            <?php
			  }
			?> 
         $('#mk').live('click',function() {
						 						 
						 tmp=parseInt(document.getElementById(this.value).textContent);
						 if(this.checked){							 
							 jum += tmp;
							 is_edit=1;
						 } else {
							 jum -= tmp;
							 is_edit=1;
						 }
						 document.getElementById("jsks").value = jum;
						 if(jum>24){
						   alert("Tidak boleh mengambil matakuliah lebih dari 24 sks !!!");
						   document.getElementById("Save").disabled = true;
						   document.getElementById("Cetak").disabled = true;
						 }else
						 {
						   document.getElementById("Save").disabled = false;
						   document.getElementById("Cetak").disabled = false;
						 }
					});																
	});
	
	       function filter_kursem(kd_prodi,noktp)
		   {
		      var ta = $("#sem_kur").val();
			  var nta = $("#sem_kur option:selected").text();
			  $("#list_krs").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='image/ajax-loader.gif' /></div>");
		      $.ajax({
											 type : "POST",
											 url : "chg_conten.php",
											 cache: false,
											 data :"idx="+3+"&kd_prodi="+kd_prodi+"&ta="+ta+"&nta="+nta+"&noktp="+noktp,
											 success : function(data){
														  $("#list_krs").html(data);
                                                      	  //for (var i=1;i<=8;i++)
                                                          //{ 
														   //oTable1=$(".display").dataTable({"bFilter": false,"bSort": false,"bPaginate": false,"bInfo": false});
														    oTable2=$("#lst_krs").dataTable({
																	"fnDrawCallback": function ( oSettings ) {
																		if ( oSettings.aiDisplay.length == 0 )
																		{
																			return;
																		}
																		 
																		var nTrs = $('#lst_krs tbody tr');
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
																				return  "Semester "+sVal;
																			},
																			"aTargets": [ 0 ]
																		}
																	],
																	"bPaginate": false,
																	"bFilter": false,
																	"bInfo": false,
																	"aaSortingFixed": [[ 0, 'asc' ]],
																	"aaSorting": [[ 1, 'asc' ]],
																	"sDom": 'lfr<"giveHeight"t>ip',
																	 "oLanguage": {
																	 "sSearch": "Search all columns:"
																	}
																});
																jum=parseInt(document.getElementById("jsks").value);
														  //}
													   }
										  });
		   }
	
	function save_krs(kd_prodi,ta,noktp)
		   {
		      
			 if(jum>0){ 
			  data1=$(":input",oTable2.fnGetNodes()).serialize();			  
			 			  
			  if(kd_prodi=="ING" || kd_prodi=="IND"){
			    var kls = $("#kls").val();			    
			  }else{
			    var kls ="A";
			  }
			  
			  
			 if(kd_prodi=="GEO" || kd_prodi=="IND" || kd_prodi=="IPS" || kd_prodi=="IP"){ 
			  var kmps = $("#kmps").val();
			 }else{
			   var kmps ="BALEENDAH";
			 }
			  $("#list_krs").html("<div id='pgload'><font size='1' color='red'>Menyimpan file ....</font> <img src='image/ajax-loader.gif' /></div>");
			  $.ajax({ 
			           type : "POST",
					   url : "save_krs.php",
					   cache: false,
					   data :data1+"&kd_prodi="+kd_prodi+"&ta="+ta+"&kmps="+kmps+"&kls="+kls+"&noktp="+noktp,
					   success : function(data){	
                                                 alert("Data berhasil di simpan !!!");
												 filter_kursem(kd_prodi,noktp);
                                              }					   
			  
			        });
		      is_edit=0;
			  }else{
			    alert("Anda belum memilih mata kuliah apapun !!!");
			  }
		   }
		   
		   function cetak_krs(kd_prodi,ta,noktp)
		   {
		      if(is_edit==1){
			    alert("Save dulu, baru cetak !!!");
			  }else{
			      
				  
				  $("#list_krs").html("<div id='pgload'><font size='1' color='red'>Mendownload file ....</font> <img src='image/ajax-loader.gif' /></div>");
				  $.ajax({ 
			           type : "POST",
				  	   url : "ctk_pdf.php",
				  	   cache: false,
				  	   data :"idx=1&kd_prodi="+kd_prodi+"&ta="+ta+"&noktp="+noktp,
				  	   success : function(data){	
                                                 var popUp;
												 popUp = window.open(data,'download');
				  								 if (popUp == null || typeof(popUp)=='undefined') { 	
	                                                alert('Hasil cetak Kartu Rencana Studi (KRS) tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
                                                 } 
                                                  else { 	
	                                               popUp.focus();
                                                }  											      												
												 //window.open("ctk_pdf.php?idx=1&kd_prodi="+kd_prodi+"&ta="+ta+"&noktp="+noktp,'_blank') 
												 filter_kursem(kd_prodi,noktp);												  
                                              }					   
			  
			        });			  
			  }
		   }
	
	$(function() {
        $( "#tanggalLahir" ).datepicker({            
            dateFormat: 'yy-mm-dd',
            changeMonth: true,
            changeYear: true,
            maxDate: "-17Y",
        minDate: "-60Y",
        yearRange: "-60:-17",
		defaultDate : <?php echo '"'.$tanggalLahir.'"' ?>
        });  
              
        $( "#tanggalMasuk" ).datepicker({            
            dateFormat: 'yy-mm-dd',
            changeMonth: true,
            changeYear: true,
            maxDate: "+0Y",
        minDate: "-6Y",
        yearRange: "-6:+0",
		defaultDate : <?php echo '"'.$tanggalMasuk.'"' ?>
        });  
              
        $( "#tanggalLulus" ).datepicker({            
            dateFormat: 'yy-mm-dd',
            changeMonth: true,
            changeYear: true,
            maxDate: "+0Y",
        minDate: "-6Y",
        yearRange: "-6:+0",
		defaultDate : <?php echo '"'.$tanggalLulus.'"' ?>
        });  
              
        $( "#tanggalYudisium" ).datepicker({            
            dateFormat: 'yy-mm-dd',
            changeMonth: true,
            changeYear: true,
            maxDate: "+0Y",
        minDate: "-6Y",
        yearRange: "-6:+0",
		defaultDate : <?php echo '"'.$tanggalYudisium.'"' ?>
        });  

    });
    
    function checkPassword(){
        var password1 = $("#password").val();
        var password2 = $("#konfirmasiPassword").val();
        
        if(password1 != password2) {
            $("#konfirmasiPassword").val('');
            alert("Konfirmasi Password Tidak Cocok"); 
        }
    };

    function checkKTP(){
        var ktp = $("#ktp").val();
        var t = $("#tanggalLahir").val();
		var sTgl = t.substr(8,2)+t.substr(5,2)+t.substr(2,2);
		if (ktp.search(sTgl)<0)
		{
			alert("tgl lahir dan nomor ktp-nya tidak cocok !"+sTgl);
			$("#tanggalLahir").val("");
		}
     };

    function thnMasukX(){
        var tglMasuk = $("#tanggalMasuk").val();
		var tgl = new Date(tglMasuk);
		var y = tgl.getFullYear();
		var sThnMasuk = y.toString();
		if($("#tahunMasuk").val()!=sThnMasuk){
		  alert("tahun masuk seharusnya "+sThnMasuk);
		}
     };

    function thnMasuk(){
        var tglMasuk = $("#tanggalMasuk").val();
		var tgl = new Date(tglMasuk)
		var ThnMasuk = tgl.getFullYear();
		var secondCombo = document.getElementById ( "tahunMasuk" );
        secondCombo.value = ThnMasuk;
		//$("#tahunMasuk").val(ThnMasuk);
		$("#batasStudi").val(ThnMasuk+7);
		};
		
	function cekform(){	  
       var t = $("#tanggalLahir").val();
       var t1 = $("#tanggalMasuk").val();	   
	   var nm = $("#namaMahasiswa").val();
	   var alm = $("#alamat").val();
	   var sma = $("#smaAsal").val();
	   
	   if (nm.trim()==""){
	     alert("Nama tidak boleh kosong, dan terdiri dari lebih satu huruf !!!");
	     return false;
	   }else if ($("#jenisKelamin").val()==""){
	     alert("Jenis Kelamin tidak boleh kosong !!!");
	     return false;
	   } else if (alm.trim()==""){
	     alert("Alamat tidak boleh kosong !!!");
	     return false;
	  } else if ($("#kota").val()==""){
	     alert("Kabupaten/kota tidak boleh kosong !!!");
	     return false;
	  } else if ($("#provinsi").val()==""){
	     alert("Provinsi tidak boleh kosong !!!");
	     return false;
	   }else if (t1==""){
	     alert("Tanggal Masuk tidak boleh kosong !!!");
	     return false;
	   } else if ($("#tahunMasuk").val()==""){
	     alert("Tahun Masuk tidak boleh kosong !!!");
	     return false;
	  } else if ($("#statusAwalMahasiswa").val()==""){
	     alert("Status Awal Mahasiswa tidak boleh kosong !!!");
	     return false;
	   }else if (t==""){
	     alert("Tanggal Lahir tidak boleh kosong !!!");
	     return false;
	   } else if ($("#statusMahasiswa").val()==""){
	     alert("Status Mahasiswa tidak boleh kosong !!!");
	     return false;
	  } else if ($("#tempatLahir").val()==""){
	     alert("Tempat Lahir tidak boleh kosong !!!");
	     return false;
	  } else if (sma.trim()==""){
	     alert("SMA asal tidak boleh kosong !!!");
	     return false;
	  } else {
	            
				
				$.ajax({ 
			           type : "POST",
				  	   url : "add_pumhs.php",
				  	   cache: false,
				  	   data :$("#user-form").serialize()+"&nomorKTP=<?php echo $nomorKTP ?>",
				  	   success : function(data){	
                                   window.location=data;
								 } 
			        });
				
				
				
	        }
	   
	   
	 };
	 
	 function isNumberKey(evt)
      {
         var charCode = (evt.which) ? evt.which : event.keyCode
         if (charCode > 31 && (charCode < 48 || charCode > 57))
            return false;

         return true;
      };	
	  
	  function logout()
      {
        window.location="index.php";

         return true;
      };	
	  
</script>

<div class="container" id="page">
<div class="clear"></div>

<div id="header">
<a href="index.php"><img src="image/header3.png" height="110" width="1000"></a>
</div><!-- header -->

<div id="wrapper" style="margin-top: -20px;">
    <!-- breadcrumbs -->


  <div id="tabs">
	<ul>
     <li><a href="#tabs-1" >Data Identitas Mahasiswa</a></li>
	 <li><a href="#tabs-2" >Kartu Rencana Studi (KRS)</a></li>
	 <li><a href="#tabs-3" >Kartu Hasil Studi (KHS)</a></li>
    </ul>	
<!-- <h1>Data Identitas Mahasiswa</h1> --> 
   <div id="tabs-1">
     <?php  include "vw_add_pumhs.php" ?>
   </div>
   <div id="tabs-2"> 
    <?php  
	  if($verifikasi==1){
    	  $vw_mtk=new vw_mtk; 
	      echo $vw_mtk->filter_kursem($prod,$nomorKTP); 
		 } else {
		    echo "Data anda belum diverifikasi oleh Program Studi !!!";
		 }
	?>  
  </div> 
    <div id="tabs-3"> 
    <?php  
	  if($verifikasi==1){
    	  $vwkrs=new vw_krs; 
	      echo $vwkrs->tb_khs($prod,$nomorKTP); 
		 } else {
		    echo "Data anda belum diverifikasi oleh Program Studi !!!";
		 }
	?>  
  </div>
    


   </div><!-- form -->



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
</body>
</html>