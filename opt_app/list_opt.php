<?php
 require_once "shared.php";
 
 
 $username = isset($_SESSION["userName"]) ? $_SESSION["userName"] : ''; 
 $password = isset($_SESSION["password"]) ? $_SESSION["password"]: ''; 
 $id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"]: '';
 $fak = isset($_SESSION["fak"]) ? $_SESSION["fak"]: ''; 
 
 
 
 $dt=new dt_operator;
 
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
        <link rel="stylesheet" type="text/css" href="css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Oxygen:400,300,700" />
        <link rel="stylesheet" type="text/css" href="../css/main.css" />
        <link rel="stylesheet" type="text/css" href="../css/form.css" />
        <!--<link rel="stylesheet" href="css/select2.css" />-->

        <link rel="icon" type="image/png" href="../image/iconunibba.png">
       <!-- <link rel="stylesheet" type="text/css" href="../../css/jquery-ui.css" />
		<link rel="stylesheet" type="text/css" href="css/jqueryslidemenu.css" />
		<script type="text/javascript" src="../../js1/jquery.js"></script>
		<script type="text/javascript" src="../../js/jquery-ui.min.js"></script>-->
		
		<script type="text/javascript" src="../js1/jquery-1.8.0.min.js"></script>
	    <script type="text/javascript" src="../js1/jquery-ui-1.8.23.custom.min.js"></script>
		
		<link type="text/css" href="../css1/jquery-ui-1.8.23.custom.css" rel="stylesheet" />
		<!--<script type="text/javascript" src="js/jqueryslidemenu.js"></script>-->
		
		<style type="text/css">
	      @import "../datatables/media/css/demo_page.css";
	      @import "../datatables/media/css/demo_table.css";
          .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 11px; }	  
        </style>
		
		<link rel="stylesheet" type="text/css" href="../css1/menu.css" />
		
		<script type="text/javascript" src="../datatables/media/js/jquery.dataTables.js"></script>
		
		<title>Pendataan Ulang Mahasiswa UNIBBA</title>
    </head>
<body>
<script type="text/javascript">
          var jum=0
		  var tmp=0;
		  var is_edit=0;
    $(document).ready(function () {
	  $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=5&fak=<?php echo $fak;?>",
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
				  
				  oTable1=$("#lst_details").dataTable({"aaSorting": []});
				  oTable1=$("#tb_login").dataTable({"aaSorting": []});
				  oTable1=$("#tb_create").dataTable({"aaSorting": []});
				  oTable1=$("#tb_update").dataTable({"aaSorting": []});
				  oTable1=$("#lst_stat_uns").dataTable({"bFilter": false,
												"bSort": false,
												"bPaginate": false,
												"bInfo": false});

				                               }
                                  });
								  
								  
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
   var oTable2,oTable4;
   function changecontent(idx)
   {
     $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	 $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx="+idx+"&fak=<?php echo $fak;?>",
									 success : function(data){
					                              $("#data").html(data);												
										          oTable2=$("#lst_mhs5").dataTable({"aaSorting": []});
												  oTable4=$("#lst_stat").dataTable();
												  oTable5=$("#lst_krs").dataTable();
												  oTable6=$("#lst_sbrnmtk").dataTable();
												  oTable7=$("#lst_nilai").dataTable();
												  oTable8=$("#lst_khs").dataTable();
												  oTable8=$("#lst_kur").dataTable();
												  $( "#tabs" ).tabs();
												  $( "#tabs2" ).tabs();	
                                                  $( "#tabs3" ).tabs();													  
												  oTable3=$(".display_ctklog").dataTable({"aaSorting": []});
												  oTable1=$(".display_entry").dataTable({"aaSorting": []});
												  oTable1=$(".display_ver").dataTable({"aaSorting": []});
				                               }
                                  });
   }
   
    function deletefile(nm)
   {
     $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	 $.ajax({
                                     type : "POST",
				                     url : "delete_file.php",
				                     cache: false,
				                     data :"nm="+nm,
									 success : function(data){
					                              changecontent(12);
				                               }
                                  });
   }
   
   function rekap_prodi(kd_prodi,kd_fak)
   {
      $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=10&kd_prodi="+kd_prodi+"&kd_fak="+kd_fak,
									 success : function(data){
					                            $("#data").html(data);												
										          $( "#tabs" ).tabs();
												  $( "#tabs2" ).tabs();
												  oTable1=$(".display_entry").dataTable({"aaSorting": []});
												  
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
															$("#tabs" ).tabs();
																								
				                               }
                                  });
   }
   
   
   function inputdtmhs(kd_fak,kd_prodi)
   {
     $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	 $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=8&kd_fak="+kd_fak+"&kd_prodi="+kd_prodi,
									 success : function(data){					                            
													
															$("#data").html(data);
															$(function() {
																	$( "#tanggalLahir" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "-17Y",
																	    minDate: "-60Y",
																	    yearRange: "-60:-17"
																	});  
																		  
																	$( "#tanggalMasuk" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "+0Y",
																	    minDate: "-6Y",
																	    yearRange: "-6:+0"
																	});  
																		  
																	$( "#tanggalLulus" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "+0Y",
																	    minDate: "-6Y",
																	    yearRange: "-6:+0"
																	});  
																		  
																	$( "#tanggalYudisium" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "+0Y",
																	    minDate: "-6Y",
																	    yearRange: "-6:+0"
																	});  

																});
															//$("#tabs" ).tabs();
																								
				                               }
                                  });
   
   
   }
   
   function editdtmhs(noktp,kd_fak)
   {
     $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	 $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=9&noktp="+noktp+"&kd_fak="+kd_fak,
									 success : function(data){					                            
													
															$("#data").html(data);
															$(function() {
																	$( "#tanggalLahir" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "-17Y",
																	minDate: "-60Y",
																	yearRange: "-60:-17"
																	});  
																		  
																	$( "#tanggalMasuk" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "+0Y",
																	    minDate: "-6Y",
																	    yearRange: "-6:+0"
																	});  
																		  
																	$( "#tanggalLulus" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "+0Y",
																	    minDate: "-6Y",
																	    yearRange: "-6:+0"
																	});  
																		  
																	$( "#tanggalYudisium" ).datepicker({            
																		dateFormat: 'yy-mm-dd',
																		changeMonth: true,
																		changeYear: true,
																		maxDate: "+0Y",
																	    minDate: "-6Y",
																	    yearRange: "-6:+0"
																	});  

																});
															//$("#tabs" ).tabs();
																								
				                               }
                                  });
   
   
   }
   
   
    
    
    function checkKTP(){
        var ktp = $("#nomorKTP").val();
        var t = $("#tanggalLahir").val();
		var sTgl = t.substr(9,1)+t.substr(5,2)+t.substr(2,2);
		if (ktp.search(sTgl)<0)
		{
			alert("tgl lahir dan nomor ktp-nya tidak cocok !");
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
		
	function cekform(flag){	  
       var t = $("#tanggalLahir").val();
       var t1 = $("#tanggalMasuk").val();	   
	   
	   if($("#nomorKTP").val()=="")
	   {
	     alert("NO KTP tidak boleh kosong !!!");
	     return false;
	   }else if ($("#namaMahasiswa").val()==""){
	     alert("Nama tidak boleh kosong !!!");
	     return false;
	   }else if ($("#jenisKelamin").val()==""){
	     alert("Jenis Kelamin tidak boleh kosong !!!");
	     return false;
	   } else if ($("#alamat").val()==""){
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
	  } else if ($("#Prodi").val()==""){
	     alert("Fakultas dan Prodi tidak boleh kosong !!!");
	     return false;
	  } else if ($("#smaAsal").val()==""){
	     alert("SMA asal tidak boleh kosong !!!");
	     return false;
	  } 
	  //else if ($("#telepon").val()==""){
	  //   alert("Telepon tidak boleh kosong !!!");
	  //   return false;
	  //} else if ($("#hp").val()==""){
	  //   alert("No. HP tidak boleh kosong !!!");
	  //   return false;
	  //}  
	  else {
	            if (flag==1){
				      data1=$("#input-form").serialize()+'&idx='+flag;
					}else{
					  data1=$("#editmhs").serialize()+'&idx='+flag;
						}							
				$.ajax({
                                     type : "POST",
				                     url : "entry_dt_mhs.php",
				                     cache: false,
				                     data : data1,									
									 success : function(data){					                            
												changecontent(3);
												alert(data.trim());	
												if (flag==1){
												  //$("#dialog2").dialog("close");
												}else{
												 // $("#dialog3").dialog("close");
												
												}
												
				                               }
                                  });
	        }
	   
	   
	 };
	 
	 function cekform1(){
	    var password1 = $("#baru").val();
        var password2 = $("#konf_baru").val();
        
        if(password1 != password2) {
            alert("Konfirmasi Password Tidak Cocok"); 
        }else{
		                  data1=$("#gnt-pass").serialize();
						  $.ajax({
                                     type : "POST",
				                     url : "gnt_pass.php",
				                     cache: false,
				                     data : data1,									
									 success : function(data){					                            
												alert(data);	
																								
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
   
     function isKTPExist(evt)
	 {
	   if ($("#nomorKTP").val()!='') {  
		 $("#ktpada").html("<div id='pgload'><font size='1' color='red'>Memeriksa KTP di Database ....</font> <img src='../image/ajax-loader.gif' /></div>");
		 $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=13&noktp="+$("#nomorKTP").val(),
									 success : function(data){
					                            $("#ktpada").html(data);
				                               }
                                  });
	   }else{
	      $("#ktpada").html('');	   
	   } 
	 };
   
   function logout()
   {
       $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=6",
									 success : function(data){
					                            window.location="index.php";
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
				                     data :"idx=17&prodi="+prodi+"&thn="+thn+"&fak="+fak+"&nmfile="+nmfile+"&idx1="+idx,
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
				                     data :"idx=16&prodi="+prodi+"&thn="+thn+"&fak="+fak,
									 success : function(data){
					                            $("#data_list_mhs").html(data);												
										        $( "#tabs" ).tabs();
												oTable1=$(".display_entry").dataTable({"aaSorting": []});
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
				                     data :"idx=18&prodi="+prodi+"&thn="+thn+"&fak="+fak+"&idx1=6&sem="+sem,
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
				                     data :"idx=18&prodi="+prodi+"&thn="+thn+"&fak="+fak+"&idx1=7&sem="+sem,
									 success : function(data){
					                            $("#data_krs").html(data);
												oTable4=$("#lst_krs").dataTable();
										        $( "#tabs3" ).tabs();												
				                               }
                                  });
   
   }

   function filter_khs(kd_fak)
   {
      $("#data_khs").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_khs").val();	
	   var prodi = $("#Prodi_khs").val();	
       var thn = $("#thn_khs").val();
	   var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=21&prodi="+prodi+"&thn="+thn+"&fak="+fak+"&idx1=10&sem="+sem,
									 success : function(data){
					                            $("#data_khs").html(data);
												oTable4=$("#lst_khs").dataTable();
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
				                     data :"idx=18&prodi="+prodi+"&thn=0&fak="+fak+"&idx1=8&sem="+sem,
									 success : function(data){
					                            $("#data_sbrnmtk").html(data);
												oTable4=$("#lst_sbrnmtk").dataTable();
										        $( "#tabs3" ).tabs();												
				                               }
                                  });
   
   }

   function filter_nilai(kd_fak)
   {
       $("#data_nilai").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_nilai").val();	
	   var prodi = $("#Prodi_nilai").val();	
       var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=18&prodi="+prodi+"&thn=0&fak="+fak+"&idx1=9&sem="+sem,
									 success : function(data){
					                            $("#data_nilai").html(data);
												oTable4=$("#lst_nilai").dataTable();
										        $( "#tabs3" ).tabs();												
				                               }
                                  });
   
   }

   function filter_kur(kd_fak)
   {
       $("#data_kur").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_kur").val();	
	   var prodi = $("#Prodi_kur").val();	
       var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=22&prodi="+prodi+"&thn=0&fak="+fak+"&idx1=11&sem="+sem,
									 success : function(data){
					                            $("#data_kur").html(data);
												oTable4=$("#lst_kur").dataTable();
										        $( "#tabs3" ).tabs();												
				                               }
                                  });
   
   }


   function save_verifikasi(kd_fak,nm_file)
   {
      
	  //data1=$("#verifikasi").serialize();
		data1=$(":input",oTable2.fnGetNodes()).serialize();	
	  $("#data_sdver").html("<div id='pgload'><font size='1' color='red'>Menyimpan Data ....</font> <img src='../image/ajax-loader.gif' /></div>");	
	  $.ajax({
               type : "POST",
	           url : "verifikasi.php",
	           cache: false,
	           data : data1+"&kd_fak="+kd_fak+"&nm_file="+nm_file,									
	           success : function(data){					                            
										filter_verifikasi(kd_fak,5);
										alert('Data berhasil di simpan !!!');																								
		                               }
            });  
   }
   
   function save_absperwalian(kd_fak,kd_prodi,sem)
   {
      
	  //data1=$("#verifikasi").serialize();
		data1=$(":input",oTable4.fnGetNodes()).serialize();	
	  $("#data_absperwalian").html("<div id='pgload'><font size='1' color='red'>Menyimpan Data ....</font> <img src='../image/ajax-loader.gif' /></div>");	
	  $.ajax({
               type : "POST",
	           url : "perwalian.php",
	           cache: false,
	           data : data1+"&kd_fak="+kd_fak+"&kd_prodi="+kd_prodi+"&sem="+sem,									
	           success : function(data){					                            
										filter_perwalian(kd_fak);
										alert('Data berhasil di simpan !!!');																								
		                               }
            });  
   }
   
   function cetak_data(kd_fak)
   {
       var prodi = $("#Prodi_hsl_val").val();	
       var thn = $("#thn_hsl_val").val();
	   var fak = kd_fak;
	   $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   $.ajax({
                                     type : "POST",
				                     url : "ctk_pdf.php",
				                     cache: false,
				                     data :"idx=1&prodi="+prodi+"&thn="+thn+"&fak="+kd_fak,
									 success : function(data){
												changecontent(3);
												var popUp;
												 popUp = window.open(data,'download');
				  								 if (popUp == null || typeof(popUp)=='undefined') { 	
	                                                alert('Hasil cetak tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
                                                 } 
                                                  else { 	
	                                               popUp.focus();
                                                }
												//window.open(data,'Download'); 												
				                               }
                                  });
   }
   
   function cetak_frm_verifikasi(kd_fak)
   {
       var prodi = $("#Prodi_frm_ver").val();	
       var thn = $("#thn_frm_ver").val();
	   var fak = kd_fak;
	   $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   $.ajax({
                                     type : "POST",
				                     url : "ctk_pdf.php",
				                     cache: false,
				                     data :"idx=2&prodi="+prodi+"&thn="+thn+"&fak="+kd_fak,
									 success : function(data){
												changecontent(14);
												
												if(data==0)
												{
												 alert("Tidak ada data untuk diverifikasi.");
												}else{
												   var popUp;
													 popUp = window.open(data,'download');
													 if (popUp == null || typeof(popUp)=='undefined') { 	
														alert('Hasil cetak tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
													 } 
													  else { 	
													   popUp.focus();
													}
												  
												  //window.open(data,'Download');
                                                 } 												
				                               }
                                  });
   }
   function cetak_hsl_verifikasi(kd_fak)
   {
       var prodi = $("#Prodi_hsl_ver").val();	
       var thn = $("#thn_hsl_ver").val();
	   var fak = kd_fak;
	   $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   $.ajax({
                                     type : "POST",
				                     url : "ctk_pdf.php",
				                     cache: false,
				                     data :"idx=3&prodi="+prodi+"&thn="+thn+"&fak="+kd_fak,
									 success : function(data){
												changecontent(14);
												
												if(data==0)
												{
												 alert("Tidak ada data untuk dicetak.");
												}else{
												   var popUp;
													 popUp = window.open(data,'download');
													 if (popUp == null || typeof(popUp)=='undefined') { 	
														alert('Hasil cetak tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
													 } 
													  else { 	
													   popUp.focus();
													}
												   
												   //window.open(data,'Download');
                                                 } 												
				                               }
                                  });
   }
   function cetak_blmlyk_verifikasi(kd_fak)
   {
       var prodi = $("#Prodi_hsl_val").val();	
       var thn = $("#thn_hsl_val").val();
	   var fak = kd_fak;
	   $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   $.ajax({
                                     type : "POST",
				                     url : "ctk_pdf.php",
				                     cache: false,
				                     data :"idx=4&prodi="+prodi+"&thn="+thn+"&fak="+kd_fak,
									 success : function(data){
												changecontent(14);
												
												if(data==0)
												{
												 alert("Tidak ada data untuk dicetak.");
												}else{
												  
												  var popUp;
													 popUp = window.open(data,'download');
													 if (popUp == null || typeof(popUp)=='undefined') { 	
														alert('Hasil cetak tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
													 } 
													  else { 	
													   popUp.focus();
													}
												  
												  //window.open(data,'Download');
                                                 } 												
				                               }
                                  });
   }
   function cetak_perwalian(kd_fak)
   {
       var prodi = $("#Prodi_absperwalian").val();	
       var thn = $("#thn_absperwalian").val();
	   var fak = kd_fak;
	   $("#data_absperwalian").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   $.ajax({
                                     type : "POST",
				                     url : "ctk_pdf.php",
				                     cache: false,
				                     data :"idx=5&prodi="+prodi+"&thn="+thn+"&fak="+kd_fak,
									 success : function(data){
												filter_perwalian(kd_fak);
                                                 if(data==0)
												{
												 alert("Tidak ada data untuk dicetak.");
												}else{
												   var popUp;
													 popUp = window.open(data,'download');
													 if (popUp == null || typeof(popUp)=='undefined') { 	
														alert('Hasil cetak Absen Perwalian tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
													 } 
													  else { 	
													   popUp.focus();
													}
												   
												   //window.open(data,'Download');
                                                 }												
				                               }
                                  });
   }
   
   function cetak_DHMD(kd_fak)
   {   $("#data_sbrnmtk").html("<div id='pgload'><font size='1' color='red'>Mencetak DHMD ....</font> <img src='../image/ajax-loader.gif' /></div>");
       var sem = $("#sem_sbrnmtk").val();	
	   var prodi = $("#Prodi_sbrnmtk").val();	
       var fak = kd_fak;	   
	   $.ajax({
                                     type : "POST",
				                     url : "ctk_excel.php",
				                     cache: false,
				                     data :"idx=1&prodi="+prodi+"&sem="+sem+"&fak="+kd_fak,
									 success : function(data){
												filter_sbrnmtk(kd_fak);
                                                 if(data==0)
												{
												 alert("Tidak ada data untuk dicetak.");
												}else{
												     var popUp;
													 popUp = window.open(data,'download');
													 if (popUp == null || typeof(popUp)=='undefined') { 	
														alert('Hasil cetak DHMD tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
													 } 
													  else { 	
													   popUp.focus();
													 }
												   
												    //window.open(data,'Download');
                                                 }												
				                               }
                                  });
   }
   
   function inputkrs(noktp)
   {
     $("#data_krs").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_krs").val();	
	   var nta = $("#sem_krs option:selected").text();
	   var prodi = $("#Prodi_krs").val();	
       var thn = $("#thn_krs").val();
	   	
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=19&prodi="+prodi+"&sem="+sem+"&nta="+nta+"&noktp="+noktp,
									 success : function(data){
					                            $("#data_krs").html(data);
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
				                               }
                                  });
   }

   function inputnilai(kode,shift,kelas,fak)
   {
     $("#data_nilai").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_nilai").val();	
	   var prodi = $("#Prodi_nilai").val();	
       
       
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx=20&prodi="+prodi+"&sem="+sem+"&kode="+kode+"&shift="+shift+"&kelas="+kelas+"&fak="+fak,
									 success : function(data){
					                            $("#data_nilai").html(data);
												oTable2=$("#lst_nilai").dataTable();                               							
				                               }
                                  });
   }
   
  function save_nilai(kode,shift,kelas,fak)
		   {
		      
			 
			  data1=$(":input",oTable2.fnGetNodes()).serialize();			  
			 var sem = $("#sem_nilai").val();	
	         var prodi = $("#Prodi_nilai").val();				  
			  
			  $("#data_nilai").html("<div id='pgload'><font size='1' color='red'>Menyimpan file ....</font> <img src='../image/ajax-loader.gif' /></div>");
			  $.ajax({ 
			           type : "POST",
					   url : "save_nilai.php",
					   cache: false,
					   data :data1+"&prodi="+prodi+"&sem="+sem+"&kode="+kode+"&shift="+shift+"&kelas="+kelas,
					   success : function(data){	
                                                 alert("Data berhasil di simpan !!!");
												 filter_nilai(fak);
                                              }					   
			  
			        });
		      
			  
		   }


   function save_krs(kd_fak,kd_prodi,ta,noktp)
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
			  $("#data_krs").html("<div id='pgload'><font size='1' color='red'>Menyimpan file ....</font> <img src='../image/ajax-loader.gif' /></div>");
			  $.ajax({ 
			           type : "POST",
					   url : "save_krs.php",
					   cache: false,
					   data :data1+"&kd_prodi="+kd_prodi+"&ta="+ta+"&kmps="+kmps+"&kls="+kls+"&noktp="+noktp,
					   success : function(data){	
                                                 alert("Data berhasil di simpan !!!");
												 filter_krs(kd_fak);
                                              }					   
			  
			        });
		      is_edit=0;
			  }else{
			    alert("Anda belum memilih mata kuliah apapun !!!");
			  }
		   }
		   
		   function cetak_krs(kd_fak,kd_prodi,ta,noktp)
		   {
		      if(is_edit==1){
			    alert("Save dulu, baru cetak !!!");
			  }else{
			      $("#data_krs").html("<div id='pgload'><font size='1' color='red'>Mendownload file ....</font> <img src='../image/ajax-loader.gif' /></div>");
				  $.ajax({ 
			           type : "POST",
					   url : "ctk_pdf.php",
					   cache: false,
					   data :"idx=6&kd_prodi="+kd_prodi+"&ta="+ta+"&noktp="+noktp,
					   success : function(data){	
                                                 var popUp;
												 popUp = window.open(data,'download');
				  								 if (popUp == null || typeof(popUp)=='undefined') { 	
	                                                alert('Hasil cetak Kartu Rencana Studi (KRS) tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
                                                 } 
                                                  else { 	
	                                               popUp.focus();
                                                }												 
												 //window.open(data,'download');
												 filter_krs(kd_fak);												  
                                              }					   
			  
			        });			  
			  }
		   }

		   function cetak_khs(kd_fak,kd_prodi,ta,noktp)
		   {
		      
			      $("#data_khs").html("<div id='pgload'><font size='1' color='red'>Mendownload file ....</font> <img src='../image/ajax-loader.gif' /></div>");
				  $.ajax({ 
			           type : "POST",
					   url : "ctk_pdf.php",
					   cache: false,
					   data :"idx=7&kd_prodi="+kd_prodi+"&ta="+ta+"&noktp="+noktp,
					   success : function(data){	
                                                 var popUp;
												 popUp = window.open(data,'download');
				  								 if (popUp == null || typeof(popUp)=='undefined') { 	
	                                                alert('Hasil cetak Kartu Hasil Studi (KHS) tidak dapat ditampilkan, matikan pop-up blocker pada browser anda !!!'); 
                                                 } 
                                                  else { 	
	                                               popUp.focus();
                                                }												 
												 //window.open(data,'download');
												 filter_khs(kd_fak);												  
                                              }					   
			  
			        });			  
			  
		   }
   
   function deletekrs(kd_fak,noktp)
   {
     $("#data_krs").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var sem = $("#sem_krs").val();	
	   var prodi = $("#Prodi_krs").val();	
       var fak = kd_fak;	
       
	  $.ajax({
                                     type : "POST",
				                     url : "delete_krs.php",
				                     cache: false,
				                     data :"prodi="+prodi+"&fak="+fak+"&sem="+sem+"&noktp="+noktp,
									 success : function(data){					                            
												filter_krs(kd_fak);												
				                               }
                                  });
   }
   
</script>


<div id="header">
<a href="index.php"><img src="../image/header3.png" height="110" width="1000"></a>
</div><!-- header -->

<div id="wrapper" style="margin-top: -20px;">
<div id="content">
	
<!-- <h1>Daftar Mahasiswa yang terdaftar</h1> -->

<!-- <div class="form">-->
<ul id="menu">
<li><a href="list_opt.php">Home</a></li>
<li><a href="javascript:changecontent(3);">List Data Mahasiswa</a></li>
<li><a href="javascript:changecontent(14);">Verifikasi</a></li>
<li><a href="javascript:changecontent(15);">Persiapan Perkuliahan</a></li>
<li><a href="javascript:changecontent(12);">Log Cetak</a></li>
<li><a href="javascript:changecontent(11);">Ganti Password</a></li>
<li><a href="javascript:logout();">Logout</a></li>
</ul> 

<div  id='data'> </div>
<!-- </div> -->
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
