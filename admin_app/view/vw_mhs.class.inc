<?php

 
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
  


include_once $base_path."dt/dt_mhs.class.inc";
include_once $base_path."dt/dt_stat_mhs.class.inc";
include_once $base_path."dt/dt_krs.class.inc";
include_once $base_path."dt/dt_mhs_epsbed.class.inc";
include_once $base_path."dt/dt_prodi.class.inc";
include_once $base_path."dt/dt_universitas.class.inc";
include_once $base_path."dt/dt_kec.class.inc";
include_once "../basic_class/html_table.class.php";
include_once "../basic_class/html_form.class.php";


class vw_mhs
{  
    var $dt_mhs;
	var $arr_thn_msk;
	var $dt_mhs_epsbed;
	function vw_mhs()
	{
	  	
        $this->dt_mhs = new dt_mhs;
        $this->dt_mhs_epsbed = new dt_mhs_epsbed;
        
		$this->arr_thn_msk=array(); 
        $tmp_date =date("Y");							
		for ($i=2006;$i<=$tmp_date;$i++){
		  $this->arr_thn_msk[$i]=$i;
		}
		
	}
	
		function entry_data2($idx=0,$fak='')
	{
	    switch($idx){
        case 1 :     
                 $sql="mhscdate is not null and date(mhscdate) = date(now())";
                 $nm="tb_create";				 
			break;
        case 2 :  
               	$sql="mhsudate is not null and date(mhsudate) = date(now())";
                $nm="tb_update";				
			break; 
		case 3 :  
                $sql="tgl_log is not null and date(tgl_log) = date(now())";
                $nm="tb_login"; 				
			break; 	
        }			
		
		if($fak<>""){
		  $sql.=" and kd_fakultas='".$fak."'";
		}
		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => $nm,"width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('KTP', null, 'header');	   
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('L/P', null, 'header');      
		$tbl->addCell('Fak. - Prodi', null, 'header');	    
        if ($idx==2)
		{
		$tbl->addCell('Validasi', null, 'header');
		}
		
		$data = $this->dt_mhs->getDataEntri($sql); 
		
		if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  $i=$i+1;
		  $tbl->addRow();        
		  $tbl->addCell($i, null, 'data');
	      $link="javascript:dtmhs(4,".$row['NO_KTP'].");";
	      $tbl->addCell("<a href='".$link."'>".$row['NO_KTP']."</a>", null, 'data');
          $tbl->addCell($row['Nama_mahasiswa'], null, 'data');
		  $tbl->addCell($row['Jenis_kelamin'], null, 'data');
		  $tbl->addCell($row['kd_fakultas'].'-'.$row['prodi'], null, 'data');         
			if ($idx==2)
		    {
		      $txt=$this->validasi($row);
			  $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		    }     
			   			 
          }
		  
		 
      }
                 
					
	  return $tbl->display("");
	}
	
		
	function validasi($row)
	{
	              $txt="";
				  $tmp_date =date("Y");
				  if(strlen($row['NO_KTP'])<16){					
					 $txt = $txt."<li>Panjang No KTP kurang dari 16 angka !!!</li>";
				   }
				   
				if(($row['Tgl_Log']==null) and ($row['optcid']==null) and ($row['optuid']==null) )
                {$txt = $txt."<li>Silahkan login untuk melengkapi data !!!</li>";}				
				else{  
					 if(($row['NIM']=="")){
						if ($row['Tahun_masuk']<$tmp_date) {  
						   $txt = $txt."<li>NIM mohon diisi</li>";
						   $cek_nim=1;
						  } else {
						    $cek_nim=1;
						  }
					  }else
					  {					
						$cek_nim=0;
						$subject =$row['NIM'];
						$pattern = "/[A-Ga-g]1[A-Ga-g][0-9]{6}/";				
						if(($row['NIM']!="") && (preg_match($pattern,$subject)==0)){
						  $txt = $txt."<li>NIM salah tulis !!!</li>";
						  $cek_nim=1;
						}else{
						  if(strcmp($row['kd_fakultas'],'FAPERTA')==0){
						     $pattern = "/[Aa]1[A-Ca-c][0-9]{6}/";
							 if((preg_match($pattern,$subject)==0)){
						        $txt = $txt."<li>Bukan NIM Fakultas Pertanian !!!</li>";
								$cek_nim=1;
						     }   
						  }else{
						    if(strcmp($row['kd_fakultas'],'FE')==0){
						       $pattern = "/[Ee]1[Aa][0-9]{6}/";
							   if((preg_match($pattern,$subject)==0)){
						          $txt = $txt."<li>Bukan NIM Fakultas Ekonomi !!!</li>";
								  $cek_nim=1;
						       }
						    }else{
                                if(strcmp($row['kd_fakultas'],'FISIP')==0){
						          $pattern = "/[Dd]1[Aa][0-9]{6}/";
							      if((preg_match($pattern,$subject)==0)){
						             $txt = $txt."<li>Bukan NIM FISIP !!!</li>";
									 $cek_nim=1;
						          }
						        }else{
						           if(strcmp($row['kd_fakultas'],'FIKES')==0){
						             $pattern = "/[Gg]1[Aa][0-9]{6}/";
							         if((preg_match($pattern,$subject)==0)){
						                $txt = $txt."<li>Bukan NIM Fakultas Kesehatan !!!</li>";
										$cek_nim=1;
						             }
						           }else{
						              if(strcmp($row['kd_fakultas'],'FMIPA')==0){
						                $pattern = "/[Ff]1[Aa][0-9]{6}/";
							            if((preg_match($pattern,$subject)==0)){
						                   $txt = $txt."<li>Bukan NIM Fakultas MIPA !!!</li>";
										   $cek_nim=1;
						                }
						              }else{
						                  if(strcmp($row['kd_fakultas'],'FKIP')==0){
						                    $pattern = "/[Bb]1[A-Da-d][0-9]{6}/";
							                if((preg_match($pattern,$subject)==0)){
						                        $txt = $txt."<li>Bukan NIM FKIP !!!</li>";
												$cek_nim=1;
						                    }else{
											
											  if(strcmp($row['kd_prodi'],'GEO')==0){
						                             $pattern = "/[Bb]1[Aa][0-9]{6}/";
							                         if((preg_match($pattern,$subject)==0)){
						                                $txt = $txt."<li>Bukan NIM Prodi Geografi !!!</li>";
												        $cek_nim=1;
						                             }     
											      }
												  
												  if(strcmp($row['kd_prodi'],'IND')==0){
						                             $pattern = "/[Bb]1[Cc][0-9]{6}/";
							                         if((preg_match($pattern,$subject)==0)){
						                                $txt = $txt."<li>Bukan NIM Prodi Bahasa Indonesia !!!</li>";
												        $cek_nim=1;
						                             }     
											      }
											      
												  if(strcmp($row['kd_prodi'],'ING')==0){
						                             $pattern = "/[Bb]1[Bb][0-9]{6}/";
							                         if((preg_match($pattern,$subject)==0)){
						                                $txt = $txt."<li>Bukan NIM Prodi Bahasa Inggris !!!</li>";
												        $cek_nim=1;
						                             }     
											      }
												  
												  if(strcmp($row['kd_prodi'],'IPS')==0){
						                             $pattern = "/[Bb]1[Dd][0-9]{6}/";
							                         if((preg_match($pattern,$subject)==0)){
						                                $txt = $txt."<li>Bukan NIM Prodi IPS !!!</li>";
												        $cek_nim=1;
						                             }     
											      }
												  
											
											}
						                  }else{
						                    if(strcmp($row['kd_fakultas'],'FTI')==0){
						                       $pattern = "/[Cc]1[A-Ba-b][0-9]{6}/";
							                   if((preg_match($pattern,$subject)==0)){
						                          $txt = $txt."<li>Bukan NIM Fakultas Teknologi Informasi !!!</li>";
												  $cek_nim=1;
						                       }else{
											   
											      if(strcmp($row['kd_prodi'],'IF')==0){
						                             $pattern = "/[Cc]1[Aa][0-9]{6}/";
							                         if((preg_match($pattern,$subject)==0)){
						                                $txt = $txt."<li>Bukan NIM Prodi Teknik Informatika !!!</li>";
												        $cek_nim=1;
						                             }     
											      }
												  
												  if(strcmp($row['kd_prodi'],'SI')==0){
						                             $pattern = "/[Cc]1[Bb][0-9]{6}/";
							                         if((preg_match($pattern,$subject)==0)){
						                                $txt = $txt."<li>Bukan NIM Prodi Sistem Informasi !!!</li>";
												        $cek_nim=1;
						                             }     
											      }
											   
											   }
						                    }
						  
						                 } 
						  
						              }
						  
						          }
						  
						        }					  
					  
						    }
						  
						  }
						
						}
						
						}
					  

					  
					  if($row['Alamat']==""){
						
						$txt = $txt."<li>Alamat mohon dilengkapi !!!</li>";
					  }				   
					   
					   if($row['Tahun_masuk']=="0000"){
						
						$txt = $txt."<li>Tahun Masuk mohon diisi !!!</li>";
					  }else{
						   
						 if(($row['Tahun_masuk'])>$tmp_date){
							$txt = $txt."<li>Tahun Masuk salah !!!</li>";
						  }else{
							
							 $parts = explode("-",$row['Tanggal_masuk']);   
							 if( ($row['Tahun_masuk']!="0000") && ($row['Tanggal_masuk'] != null) && ($parts[0]!=$row['Tahun_masuk'])){
								 
                                 if($row['Tanggal_masuk'] == "0000-00-00"){
                                    $tmp_tgl=$row['Tahun_masuk']."-09-23";	
                                 }									
								 else {
  								    $tmp_tgl=$row['Tahun_masuk'].'-'.$parts[1].'-'.$parts[2]; 
									
								  }
								  $this->dt_mhs->update_tgl_msk($row['NO_KTP'],$tmp_tgl);
								  //$txt = $txt."<li>Tahun  Masuk dan Tanggal Masuk tak sesuai</li>";
							 }
                             
                             if($cek_nim==0){
							    if( ($row['Tahun_masuk']!="0000")){		
								  $tmp1=substr($row['NIM'],4,1);
								  $tmp2=substr($row['Tahun_masuk'],3,1);
								 if(strcmp($tmp1,$tmp2)!=0) {
								   $txt = $txt."<li>Tahun  Masuk dan NIM tak sesuai</li>";
								 } 
							 }
							 
							 }							 
							 
						  }
					  
					  }
					   
					   
						if(strlen($row['NO_KTP'])==16) 
						{				   				   
							$subject =$row['NO_KTP'];
							$pattern = "/[1 3][1-8][0-2 7][0-9][0-4][0-9][0-7][0-9][0-1][0-9][0-1 5-9][0-9]{4}/";				
				  
						  if(preg_match($pattern,$subject)==0){
						     $pattern = "/12345[0-6][0-9]{8}/";							 
							 if(preg_match($pattern,$subject)==0){
							   //$dt_kec = new dt_kec;
                               //if($dt_kec->cek_kec($subject)==0){
								  $txt = $txt."<li>PUMHS tidak mengenali format no KTP anda, silakan hubungi operator untuk mengisi form PUMHS Off line !!!</li>";
							   //}
							 }
						  }
						  
								if($row['Tanggal_lahir']=="0000-00-00"){
									$txt = $txt."<li>Tgl lahir harap diisi !!!</li>";
								}  
								else{ 
								  //$tmp = date('dmy',strtotime($row['Tanggal_lahir']));
								  //if($row['Jenis_kelamin']=='P'){
									 $parts = explode("-",$row['Tanggal_lahir']);
									 //$tmp = intval($parts[2])+40;
									 $tmp = intval($parts[2]) % 10;
									 $tmp = $tmp.$parts[1].(substr($parts[0],-2));
								  //}					  
								  
								  
								  $tmp1 = substr($row['NO_KTP'],7,5);
								  
								   if($tmp!=$tmp1){									
									$txt = $txt."<li>Tgl lahir tidak sesuai KTP, silakan login untuk memperbaiki !!!</li>";
								   }
								  
								} 
						  
					  }
					   



					   
					   if($txt=="")
						{
						$txt = "<li>Data Lengkap</li>";
						   $this->dt_mhs->update_validasi($row['NO_KTP'],1);
						    if( $row['verifikasi']==0 and $this->dt_mhs_epsbed->is_exist($row['NIM'],$row['Nama_mahasiswa'])){
							   $optudate= date("Y-m-d H:i:s");
							   $this->dt_mhs->update_verifikasi($row['NO_KTP'],1,$optudate,"System");							
							  }	
						}else{
						  if(($txt=="<li>NIM mohon diisi</li>") && (($row['NIM']=="") &&($row['Tahun_masuk']==2013)))
                          {
						     $this->dt_mhs->update_validasi($row['NO_KTP'],1);
							  if( $row['verifikasi']==0 and $this->dt_mhs_epsbed->is_exist($row['NIM'],$row['Nama_mahasiswa'])){
							   $optudate= date("Y-m-d H:i:s");
							   $this->dt_mhs->update_verifikasi($row['NO_KTP'],1,$optudate,"System");							
							  }	
						  }else{						  
						     $this->dt_mhs->update_validasi($row['NO_KTP'],0);
						   }
						}
						
						
						
						
					}	
	  return $txt;
	}
	
	function data_mhs($ktp)
	{
	
	$this->dt_mhs->KTPada($ktp);

	$prod = $this->dt_mhs->prod; 
	$Nama_mahasiswa = $this->dt_mhs->Nama_mahasiswa;
	$jenisKelamin  = $this->dt_mhs->jenisKelamin;
	$tanggalLahir  = $this->dt_mhs->tanggalLahir;
	$tahunMasuk  = $this->dt_mhs->tahunMasuk;
	$kelas = $this->dt_mhs->kelas;
	$nim  = $this->dt_mhs->nim;
	$status  = $this->dt_mhs->status;
	$status_awl  = $this->dt_mhs->status_awl;
	$tempatLahir  = $this->dt_mhs->tempatLahir;
	$alamat  = $this->dt_mhs->alamat;
	$kota  = $this->dt_mhs->kota;
	$telepon  = $this->dt_mhs->telepon;
	$provinsi  = $this->dt_mhs->provinsi;
	$hp  = $this->dt_mhs->hp;
	$kodePos  = $this->dt_mhs->kodePos;
	$tanggalLulus  = $this->dt_mhs->tanggalLulus;
	$tanggalMasuk  = $this->dt_mhs->tanggalMasuk;
	$ipkAkhir  = $this->dt_mhs->ipkAkhir;
	$nomorSkYudisium  = $this->dt_mhs->nomorSkYudisium;
	$batasStudi  = $this->dt_mhs->batasStudi;
	$tanggalYudisium  = $this->dt_mhs->tanggalYudisium;
	$nomorSeriIjazah  = $this->dt_mhs->nomorSeriIjazah;
	$smaAsal  = $this->dt_mhs->smaAsal;
	$sksDiakui  = $this->dt_mhs->sksDiakui;
	$namaTempatPekerjaan  = $this->dt_mhs->namaTempatPekerjaan;
	$kodePekerjaan  = $this->dt_mhs->kodePekerjaan;
	$prodiAsal  = $this->dt_mhs->prodiAsal;
    $universitasAsal  = $this->dt_mhs->universitasAsal;
	
	$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs","width"=>"100%"));
	
	$tbl->addRow();
	$tbl->addCell("Nomor KTP", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($ktp, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Nomor Pokok Mahasiswa", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($nim, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Nama Mahasiswa", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($Nama_mahasiswa, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Tempat Lahir", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($tempatLahir, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Tanggal Lahir", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($tanggalLahir, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Jenis Kelamin", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell(($jenisKelamin == "P") ? "Perempuan":"Laki-laki", null, 'data');
	$tbl->addRow();
	$tbl->addCell("Alamat", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($alamat, null, 'data');
	
	$txt_kota="";
	switch($kota)
					{
					case "121451" : $txt_kota="Kota Bandung"; break;
					case "121452" : $txt_kota="Kabupaten Bandung";break;
					case "121453"  : $txt_kota="Kota Cimahi";break;
					case "121454" : $txt_kota="Kabupaten Sumedang";break;
					case "121455" : $txt_kota="Kabupaten Cianjur";break;
                    }   
	$tbl->addRow();
	$tbl->addCell("Kabupaten / Kota", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($txt_kota, null, 'data');
	
	
	 $stat_prov="";
	 switch($provinsi)
			 {
				case "121" : $stat_prov="Jawa Barat";break;
				case "122" : $stat_prov="Jawa Tengan";break;
				case "123" : $stat_prov="Jawa Timur";break;
				case "124" : $stat_prov="DI Jogjakarta";break;
				case "125" : $stat_prov="DKI Jakarta";break;
                
             }
	
	$tbl->addRow();
	$tbl->addCell("Provinsi", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($stat_prov, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Kode Pos", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($kodePos, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Telepon", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($telepon, null, 'data');
	$tbl->addRow();
	$tbl->addCell("No. HP", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($hp, null, 'data');
	       
        $txt_prod="";
	    $dt_prodi=new dt_prodi;
		$data = $dt_prodi->getData("kd_prodi = '".$prod."'");
		foreach ($data as $r)
		{
			$txt_prod=$r['kd_fakultas']."-".$r['prodi'];
		}
	
	
	$tbl->addRow();
	$tbl->addCell("Fakultas dan Prodi", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($txt_prod, null, 'data');	
	$tbl->addRow();
	$tbl->addCell("Tanggal Masuk", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($tanggalMasuk, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Tahun Masuk", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($tahunMasuk, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Batas_Studi", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($batasStudi, null, 'data');
	$txt_stat="";
	switch($status){				 
			 case "A" : $txt_stat="Aktif"; break;
			 case "C" : $txt_stat="Cuti"; break;
			 case "L" : $txt_stat="Lulus"; break;				 
		 } 	
	
	$tbl->addRow();
	$tbl->addCell("Status Mahasiswa", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($txt_stat, null, 'data');
	$tbl->addRow();
	$tbl->addCell("Kelas", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($kelas=="R" ? "Reguler" : "Non Reguler", null, 'data');
	$tbl->addRow();
	$tbl->addCell("Status Awal Mahasiswa", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($status_awl=="B"? "Baru":"Pindahan", null, 'data');
	
	$tbl2 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs","width"=>"100%"));
	$tbl2->addRow();
	$tbl2->addCell("SMA Asal", null, 'data');$tbl2->addCell(":", null, 'data');$tbl2->addCell($smaAsal, null, 'data');
	
    
	$tbl5 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs","width"=>"100%"));
	
	$tbl5->addRow();
	$tbl5->addCell("Tanggal Lulus", null, 'data');$tbl5->addCell(":", null, 'data');$tbl5->addCell($tanggalLulus, null, 'data');
	$tbl5->addRow();
	$tbl5->addCell("IPK Akhir", null, 'data');$tbl5->addCell(":", null, 'data');$tbl5->addCell($ipkAkhir, null, 'data');
    $tbl5->addRow();
	$tbl5->addCell("Nomor SK Yudisium", null, 'data');$tbl5->addCell(":", null, 'data');$tbl5->addCell($nomorSkYudisium, null, 'data');
	$tbl5->addRow();
	$tbl5->addCell("Tanggal Yudisium", null, 'data');$tbl5->addCell(":", null, 'data');$tbl5->addCell($tanggalYudisium, null, 'data');
	$tbl5->addRow();
	$tbl5->addCell("Nomor Seri Ijazah", null, 'data');$tbl5->addCell(":", null, 'data');$tbl5->addCell($nomorSeriIjazah, null, 'data');
	
	
	

	
	
	$tbl3 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs","width"=>"100%"));
	
	$txt_uni="";
	$dt_universitas=new dt_universitas;
					$data = $dt_universitas->getData("Kode_Univ='".$universitasAsal."'");
					if(!empty($data))
					 foreach($data as $r){
					  $txt_uni=$r['Kode_Univ']."-".$r['Nama_Univ'];
				     }
	
	
	$tbl3->addRow();
	$tbl3->addCell("Perguruan Tinggi Asal", null, 'data');$tbl3->addCell(":", null, 'data');$tbl->addCell($txt_uni, null, 'data');
		
	
	                $dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_prodi='".$prod."'");
					$txt_fak="";
					foreach ($data as $r){
						
						$txt_fak=$r['kd_fakultas']."-".$r['prodi'];
					}

	
	$tbl3->addRow();
	$tbl3->addCell("Fakultas dan Prodi asal", null, 'data');$tbl3->addCell(":", null, 'data');$tbl3->addCell($txt_fak, null, 'data');
	
    $tbl3->addRow();
	$tbl3->addCell("Jumlah SKS diakui", null, 'data');$tbl3->addCell(":", null, 'data');$tbl3->addCell($sksDiakui, null, 'data');
	          
     				
    

	
	$tbl4 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs","width"=>"100%"));
	
	   $txt_stat="";
           switch($kodePekerjaan){
                    case "J" : $txt_stat="Belum bekerja"; break;
					case "G" : $txt_stat="Pegawai Swasta"; break;
					case "I" : $txt_stat="Wiraswasta"; break;
					case "H" : $txt_stat="LSM";break;
					case "E" : $txt_stat="PNS Lembaga Pemerintahan"; break;
					case "K" : $txt_stat="Guru honor"; break;
					case "D" : $txt_stat="Dosen PTS"; break;
					case "C" : $txt_stat="Dosen DPK PTS"; break;
					case "B" : $txt_stat="Dosen kontrak PTN/ BHMN"; break;
					case "A" : $txt_stat="Dosen PNS PTN/ BHMN"; break;
					case "F" : $txt_stat="TNI/POLRI"; break;
            } 
	
	$tbl4->addRow();
	$tbl4->addCell("Status Kerja", null, 'data');$tbl4->addCell(":", null, 'data');$tbl4->addCell($txt_stat, null, 'data');
	$tbl4->addRow();
	$tbl4->addCell("Nama Tempat Bekerja", null, 'data');$tbl4->addCell(":", null, 'data');$tbl4->addCell($namaTempatPekerjaan, null, 'data');
	
	
	

	        $txt2="<BR><center><H1>BIODATA MAHASISWA</H1></center><BR>";
			
			$txt2.="<ol>";
			$txt2.="<li>Data Mahasiswa<br><br>".$tbl->display('')."<br></li>";
			$txt2.="<li>Data Asal SMA/SMK/MA/Sederajat<br><br>".$tbl2->display('')."<br></li>";
			$txt2.="<li>Data Perguruan Tinggi Asal (diisi oleh mahasiswa pindahan atau lanjutan)<br><br>".$tbl3->display('')."<br></li>";
			$txt2.="<li>Informasi Pekerjaan(diisi oleh mahasiswa yang sudah bekerja)<br><br>".$tbl4->display('')."<br></li>";
			$txt2.="<li>Informasi Kelulusan(diisi oleh mahasiswa yang sudah lulus)<br><br>".$tbl5->display('')."<br></li>";
			$txt2.="</ol>"; 
		 
	 return $txt2;
	}
	
	
	function lst_entry_data($fak="",$kd_prodi="",$id_opt="",$idx=0,$id="lst_mhs",$lyk=0,$thn_msk=0,$proses=0)
	{
	 

     $tbl = new HTML_Table(null, 'display_ver', 0, 0, 0,array("id" => $id,"width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('KTP', null, 'header');	   
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('L/P', null, 'header');
        $tbl->addCell('Tahun Masuk', null, 'header');		
		if($kd_prodi==""){
		   $tbl->addCell('Fak. - Prodi', null, 'header');	    
       	}
		$tbl->addCell('Validasi', null, 'header');
		
		$sql="";
		if($fak<>""){
		  $sql="kd_fakultas='".$fak."' and ";
		}
		
		if($kd_prodi<>""){
		  $sql.="kd_prodi='".$kd_prodi."' and ";
		}
		
		$sql.="verifikasi=".$idx." and ";
		
		if($id_opt<>""){
		  $sql.="optcid='".$id_opt."' and ";
		}		
		
		if($thn_msk>0)
		{
		  $sql.="Tahun_masuk=".$thn_msk." and ";
		}
		
		switch($proses){		 
		case 1 : $sql.="nm_file<>'' and ";
		         break;
		case 2 : $sql.="nm_file = '' and ";
		         break;
		}
				
		switch($lyk){
		    case 0 :
			         $sql.=" validasi=1 ";
			         break;
		    case 1 :
			         $sql.=" validasi=0 "; 
			         break;
		    case 2 :
			          $sql.=" validasi=1 ";
			         break;
		  }
		
		$data = $this->dt_mhs->getDataEntri($sql); 
		
		if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  
		  $txt=$this->validasi($row);
		  
		    $i=$i+1;
		    $tbl->addRow();        
		    $tbl->addCell($i, null, 'data');
		    if($id_opt<>""){
		      $link='javascript:editdtmhs("'.$row['NO_KTP'].'","'.$fak.'");';
		    }else{
		      $link="javascript:dtmhs(4,".$row['NO_KTP'].");";
	        }
		    $tbl->addCell("<a href='".$link."'>".$row['NO_KTP']."</a>", null, 'data');	
            $tbl->addCell($row['Nama_mahasiswa'], null, 'data');
		    $tbl->addCell($row['Jenis_kelamin'], null, 'data');
		    $tbl->addCell($row['Tahun_masuk'], null, 'data');
		    if($kd_prodi==""){
		      $tbl->addCell($row['kd_fakultas'].'-'.$row['prodi'], null, 'data');         
		    }		  
		    $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		  
		}
		  
		 
      }
	 
	 return $tbl->display("");
	}
	
	
   function lst_entry_data2($kd_prodi="",$id="lst_mhs",$idx_opt=0)
	{
	 

     $tbl = new HTML_Table(null, 'display_ver', 0, 0, 0,array("id" => $id,"width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('KTP', null, 'header');	   
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('L/P', null, 'header');
        $tbl->addCell('Tahun Masuk', null, 'header');		
		$tbl->addCell('Validasi', null, 'header');
		
		$sql="";
				
		if($kd_prodi<>""){
		  $sql.="kd_prodi='".$kd_prodi."' and ";
		}
						
		if($idx_opt<>0){
		  $sql.="optcid <>''";
		}else
          {
		    $sql.="optcid is null";
		  }  		
		
		
		
		$data = $this->dt_mhs->getDataEntri($sql); 
		
		if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  
		  $txt=$this->validasi($row);
		  
		    $i=$i+1;
		    $tbl->addRow();        
		    $tbl->addCell($i, null, 'data');
		    $link="javascript:dtmhs(4,".$row['NO_KTP'].");";
	        $tbl->addCell("<a href='".$link."'>".$row['NO_KTP']."</a>", null, 'data');	
            $tbl->addCell($row['Nama_mahasiswa'], null, 'data');
		    $tbl->addCell($row['Jenis_kelamin'], null, 'data');
		    $tbl->addCell($row['Tahun_masuk'], null, 'data');
		    $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		  
		}
		  
		 
      }
	 
	 return $tbl->display("");
	}
	
	
	
	function entry_data($kd_prodi="",$id_opt="")
	{
	   


       
	        $txt='<div id="tabs">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Data Diinput Mahasiswa</a></li>';
			$txt.='<li><a href="#tabs-2">Data Diinput Operator</a></li>';
			$txt.='</ul>';
			$txt.='<div id="tabs-1">';						
			$txt.="<div>".$this->lst_entry_data2($kd_prodi,"lstmhs1")."</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			$txt.="<div>".$this->lst_entry_data2($kd_prodi,"lstmhs2",1)."</div>";
			$txt.='</div>';			
			$txt.='</div>';
	   

	   				 
				
	  return $txt;
	}
	
	function list_mhs()
	{
	                $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");					
					$vkd_prodi="";
					$vkd_fak="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vkd_fak=$r['kd_fakultas'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
					}
       	
		            $thn_msk = 2008;
                    $txt2 = "";					
					foreach($this->arr_thn_msk as $idx=>$val){
					  if($thn_msk==$val){
					    $txt2.= "<option value='$val' selected='selected' >$val</option>";
					  }else{
					    $txt2.= "<option value='$val'>$val</option>";
					  }					
                    }
      
	  $tmp='"'.$vkd_fak.'"';
	  $txt = "<fieldset>";
	  $txt=$txt."<legend>Filter: </legend>";	  
	  $txt_prodi='<select name="Prodi_hsl_val" id="Prodi_hsl_val">'.$txt1.'</select>';
	  $txt_angkatan='<select name="thn_hsl_val" id="thn_hsl_val">'.$txt2.'</select>';
	  $frm = new HTML_Form();
	  $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_list_mhs('')"));//."<button onclick='cetak_data(".$tmp.")'>Cetak Data</button>";
	  $txt.="</fieldset>";

	  $txt.="<div id = 'data_list_mhs'>";
	  $txt.=$this->filter_list_mhs($vkd_fak,$vkd_prodi,$thn_msk);
	  $txt.="</div>";
	  		
	  return $txt;
	}
	
	function filter_list_mhs($fak="",$kd_prodi,$thn_msk)
    {
	   $dt_prodi=new dt_prodi;
	   $data = $dt_prodi->getData("kd_prodi='".$kd_prodi."'");
	   $vkd_fak="";
	   foreach ($data as $r){
	     $vnm_prodi=$r['prodi'];
         $vkd_fak=$r['kd_fakultas'];		 
	   }
	   
	   $txt= "<fieldset>";
	   $txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend>";
       	$txt.='<div id="tabs">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Data Diinput Mahasiswa</a></li>';
			$txt.='<li><a href="#tabs-2">Data Diinput Operator</a></li>';
			$txt.='</ul>';
			$txt.='<div id="tabs-1">';						
			$txt.="<div>".$this->lst_entry_data1($vkd_fak,$kd_prodi,"lstmhs1",$thn_msk)."</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			$txt.="<div>".$this->lst_entry_data1($vkd_fak,$kd_prodi,"lstmhs2",$thn_msk,1)."</div>";
			$txt.='</div>';
			
			$txt.='</div>';
	  $txt.="</fieldset><br>";
	  return $txt;  
	}
	
	
	function filter_verifikasi()
	{
	  		        $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");
					$vkd_fak="";
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_fak=$r['kd_fakultas'];
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
					}
       	
		            $thn_msk = 2008;
                    $txt2 = "";					
					foreach($this->arr_thn_msk as $idx=>$val){
					  if($thn_msk==$val){
					    $txt2.= "<option value='$val' selected='selected' >$val</option>";
					  }else{
					    $txt2.= "<option value='$val'>$val</option>";
					  }					
                    }
					
					//$txt3="";
					//$dt_mhs=new dt_mhs;
					//$data = $dt_mhs->get_nm_file('kd_fakultas="'.$kd_fak.'"');
					
					//$nm_file="";
					//foreach ($data as $r){
					//	$nm_file1='"'.$r['nm_file'].'"';
					//	if($nm_file=="")
					//	{
					//	  
					//	  $nm_file=$r['nm_file'];						  
					//	  $txt3.= "<option selected='selected' value=".$nm_file1.">".$r['nm_file']."  (".$r['jml_ver']."/".$r['jml'].")"."</option>";
					//	}
					//	else{
					//	$txt3.= "<option value=".$nm_file1.">".$r['nm_file']."  (".$r['jml_ver']."/".$r['jml'].")"."</option>";
					//	}
				//	}
					
      
	  
	  	
            $tmp='"'.$vkd_fak.'"';
            $txt='<div id="tabs2">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Data Belum Layak Verifikasi</a></li>';
			$txt.='<li><a href="#tabs-2">Data Layak Verifikasi</a></li>';
			$txt.='<li><a href="#tabs-5">Data Sedang Diverifikasi</a></li>';
			$txt.='<li><a href="#tabs-3">Data Lolos Verifikasi</a></li>';
			$txt.='<li><a href="#tabs-4">Data Tidak Lolos Verifikasi</a></li>';
			$txt.='</ul>';
			$txt.='<div id="tabs-1">';	
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_prodi='<select name="Prodi_hsl_val" id="Prodi_hsl_val">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_hsl_val" id="thn_hsl_val">'.$txt2.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('',1)"));//"<button onclick='cetak_blmlyk_verifikasi(".$tmp.")'>Cetak Belum Layak Verfikasi</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_blm_lyk'>";
			$txt.=$this->hsl_filter($vkd_prodi,$thn_msk,1);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_prodi='<select name="Prodi_frm_ver" id="Prodi_frm_ver">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_frm_ver" id="thn_frm_ver">'.$txt2.'</select>';	  
	        $frm = new HTML_Form();
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('',2)"));//"<button onclick='cetak_frm_verifikasi(".$tmp.")'>Cetak Form Verfikasi</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_lyk'>";
			$txt.=$this->hsl_filter($vkd_prodi,$thn_msk,2);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-3">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_prodi='<select name="Prodi_hsl_ver" id="Prodi_hsl_ver">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_hsl_ver" id="thn_hsl_ver">'.$txt2.'</select>';	  
	        $frm = new HTML_Form();
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('',3)"));//"<button onclick='cetak_hsl_verifikasi(".$tmp.")'>Cetak Hasil Verfikasi</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_lls'>";
			$txt.=$this->hsl_filter($vkd_prodi,$thn_msk,3);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-4">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_prodi='<select name="Prodi_tlls" id="Prodi_tlls">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_tlls" id="thn_tlls">'.$txt2.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('',4)"));
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_tlls'>";
			$txt.=$this->hsl_filter($vkd_prodi,$thn_msk,4);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-5">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	       	//$txt_nmfile='<select name="nmfile" id="nmfile">'.$txt3.'</select>';
			$frm = new HTML_Form();
	        //$txt.= "Nama File ".$txt_nmfile.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."',5)"));
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_sdver'>";
			//$txt.=$this->list_verifikasi_mhs($nm_file);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='</div>';				 
	  
	  
	  //$txt.="</fieldset>";
	  return $txt;
	}
	
	function hsl_filter($kd_prodi="",$thn_msk=0,$idx,$nmfile="",$ta=0)
	{
	   
	 
       $dt_prodi=new dt_prodi;
	   $data = $dt_prodi->getData("kd_prodi='".$kd_prodi."'");
	   foreach ($data as $r){
	     $vnm_prodi=$r['prodi']; 
         $kd_fak=$r['kd_fakultas'];		 
	   }
	
	if($idx!=5 and $idx!=6 and $idx!=7 and $idx!=8){
	   $txt= "<fieldset>";
	   $txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend><div>";
	 } 
	 switch($idx)
     { 	 
	  case 1 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",0,"lst_mhs1",1,$thn_msk); break;
      case 2 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",0,"lst_mhs2",2,$thn_msk,2); break;
	  case 5 : $txt=$this->list_verifikasi_mhs($kd_fak,$nmfile); break;
	  case 3 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",1,"lst_mhs3",0,$thn_msk); break;
	  case 4 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",2,"lst_mhs4",0,$thn_msk); break;
	  case 6 : $txt=$this->list_absperwalian($kd_fak,$kd_prodi,$thn_msk,$ta); break;
	  case 7 : $txt=$this->list_krs($kd_fak,$kd_prodi,$thn_msk,$ta); break;
	  case 8 : $txt=$this->list_sbrnmtk($kd_fak,$kd_prodi,$ta); break;
	 } 
	if($idx!=5 and $idx!=6 and $idx!=7 and $idx!=8){ 
	 $txt.= "</div></fieldset>";
	} 
	  
	  return $txt;
	}
	
	
	function lst_entry_data1($fak="",$kd_prodi="",$id="lst_mhs",$thn_msk=0,$opt=0)
	{
	 

     $tbl = new HTML_Table(null, 'display_entry', 0, 0, 0,array("id" => $id,"width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('KTP', null, 'header');	   
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('L/P', null, 'header');
        $tbl->addCell('Tahun Masuk', null, 'header');		
		if($kd_prodi==""){
		   $tbl->addCell('Fak. - Prodi', null, 'header');	    
       	}
		$tbl->addCell('Validasi', null, 'header');
		
		$sql="";
		if(($fak<>"" and $kd_prodi<>"")){
		  $sql="kd_fakultas='".$fak."' and ";
		}else {
		  $sql="kd_fakultas='".$fak."'";
		}
		
		if(($kd_prodi<>"" and $thn_msk>0)){
		  $sql.="kd_prodi='".$kd_prodi."' and ";
		} else {
		  if($kd_prodi<>""){
		  $sql.="kd_prodi='".$kd_prodi."'";
		  }
		}	
		
		if($opt==0){
		  $sql.=" (optcid IS NULL OR optcid='') and ";
		}else {
		    $sql.=" (optcid IS not NULL OR optcid<>'') and ";	  
		}

        if($thn_msk>0){
		  $sql.="Tahun_masuk=".$thn_msk."";
		}
		
			
		$data = $this->dt_mhs->getDataEntri($sql); 
		
		if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  
		  $txt=$this->validasi($row);
		  
		    $i=$i+1;
		    $tbl->addRow();        
		    $tbl->addCell($i, null, 'data');
		    $link="javascript:dtmhs(4,".$row['NO_KTP'].");";
	       
		    $tbl->addCell("<a href='".$link."'>".$row['NO_KTP']."</a>", null, 'data');	
            $tbl->addCell($row['Nama_mahasiswa'], null, 'data');
		    $tbl->addCell($row['Jenis_kelamin'], null, 'data');
		    $tbl->addCell($row['Tahun_masuk'], null, 'data');
		    if($kd_prodi==""){
		      $tbl->addCell($row['kd_fakultas'].'-'.$row['prodi'], null, 'data');         
		    }		  
		    $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		  
		}
		  
		 
      }
	 
	 return $tbl->display("");
	}
	
	function persiapan_kuliah()
	{
	        $txt='<div id="tabs3">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Perwalian</a></li>';
			$txt.='<li><a href="#tabs-2">Kartu Rencana Studi</a></li>';
			$txt.='<li><a href="#tabs-3">Sebaran Matakuliah</a></li>';
			$txt.='</ul>';
			$txt.='<div id="tabs-1">';						
			$txt.=$this->tab_perwalian();
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			$txt.=$this->tab_krs();
			$txt.='</div>';
            $txt.='<div id="tabs-3">';
			$txt.=$this->tab_sbrnmtk();
			$txt.='</div>';				
			$txt.='</div>';
	   
	   
	   return  $txt;
	}
	
	function tab_sbrnmtk()
	{
	 $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");
					$kd_fak="";
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $kd_fak=$r['kd_fakultas'];
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
					}
       	
		            			
	                $ta = 20141;					
					$txt3 = "";					
					foreach($this->arr_thn_msk as $idx=>$val){
					  for($i=1;$i<=2;$i++){
					    $tmp_ta=$val.$i;
					    if($ta==$tmp_ta){
					      if($i==1){  
							 $txt3.= "<option value='$tmp_ta' selected='selected' >Ganjil $val</option>";
						  }else{
							$txt3.= "<option value='$tmp_ta' selected='selected' >Genap $val</option>";
							}
					    }else{
					      if($i==1){ 
						   $txt3.= "<option value='$tmp_ta'>Ganjil $val</option>";
						  }else{
						   $txt3.= "<option value='$tmp_ta'>Genap $val</option>";
						  } 
					    }		
					  }				  
					  			
                    } 
			
			$tmp='"'.$kd_fak.'"';
			$txt = "";
	        $txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_sem='<select name="sem_sbrnmtk" id="sem_sbrnmtk">'.$txt3.'</select>';
			$txt_prodi='<select name="Prodi_sbrnmtk" id="Prodi_sbrnmtk">'.$txt1.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." ".$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_sbrnmtk('".$kd_fak."')"));//"<button onclick='cetak_DHMD(".$tmp.")'>Cetak DHMD</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_sbrnmtk'>";
			$txt.=$this->hsl_filter($vkd_prodi,0,8,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	}
	
	
	function tab_krs()
	{
	 $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");
					$kd_fak="";
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $kd_fak=$r['kd_fakultas'];
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
					}
       	
		            $thn_msk = 2008; 
					$txt2 = "";					
					foreach($this->arr_thn_msk as $idx=>$val){
					  if($thn_msk==$val){
					    $txt2.= "<option value='$val' selected='selected' >$val</option>";
					  }else{
					    $txt2.= "<option value='$val'>$val</option>";
					  }					
                    }
			
	                $ta = 20141; 
					$txt3 = "";					
					foreach($this->arr_thn_msk as $idx=>$val){
					  for($i=1;$i<=2;$i++){
					    $tmp_ta=$val.$i;
					    if($ta==$tmp_ta){
					      if($i==1){  
							 $txt3.= "<option value='$tmp_ta' selected='selected' >Ganjil $val</option>";
						  }else{
							$txt3.= "<option value='$tmp_ta' selected='selected' >Genap $val</option>";
							}
					    }else{
					      if($i==1){ 
						   $txt3.= "<option value='$tmp_ta'>Ganjil $val</option>";
						  }else{
						   $txt3.= "<option value='$tmp_ta'>Genap $val</option>";
						  } 
					    }		
					  }				  
					  			
                    } 
			
			$tmp='"'.$kd_fak.'"';
			$txt = "";
	        $txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_sem='<select name="sem_krs" id="sem_krs">'.$txt3.'</select>';
			$txt_prodi='<select name="Prodi_krs" id="Prodi_krs">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_krs" id="thn_krs">'.$txt2.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_krs('".$kd_fak."')"));//"<button onclick='cetak_jml_sks(".$tmp.")'>Cetak Jumlah SKS</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_krs'>";
			$txt.=$this->hsl_filter($vkd_prodi,$thn_msk,7,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	}
	
	function tab_perwalian()
	{
	            $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");
					$kd_fak="";
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $kd_fak=$r['kd_fakultas'];
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
					}
       	
		            $thn_msk = 2008; 
					$txt2 = "";					
					foreach($this->arr_thn_msk as $idx=>$val){
					  if($thn_msk==$val){
					    $txt2.= "<option value='$val' selected='selected' >$val</option>";
					  }else{
					    $txt2.= "<option value='$val'>$val</option>";
					  }					
                    }
			
	                $ta = 20141; 
					$txt3 = "";					
					foreach($this->arr_thn_msk as $idx=>$val){
					  for($i=1;$i<=2;$i++){
					    $tmp_ta=$val.$i;
					    if($ta==$tmp_ta){
					      if($i==1){  
							 $txt3.= "<option value='$tmp_ta' selected='selected' >Ganjil $val</option>";
						  }else{
							$txt3.= "<option value='$tmp_ta' selected='selected' >Genap $val</option>";
							}
					    }else{
					      if($i==1){ 
						   $txt3.= "<option value='$tmp_ta'>Ganjil $val</option>";
						  }else{
						   $txt3.= "<option value='$tmp_ta'>Genap $val</option>";
						  } 
					    }		
					  }				  
					  			
                    } 
			
			$tmp='"'.$kd_fak.'"';
			$txt = "";
	        $txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_sem='<select name="sem_absperwalian" id="sem_absperwalian">'.$txt3.'</select>';
			$txt_prodi='<select name="Prodi_absperwalian" id="Prodi_absperwalian">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_absperwalian" id="thn_absperwalian">'.$txt2.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_perwalian('".$kd_fak."')"));//"<button onclick='cetak_perwalian(".$tmp.")'>Cetak Absensi Perwalian</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_absperwalian'>";
			$txt.=$this->hsl_filter($vkd_prodi,$thn_msk,6,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	
	}
	
	
	private function ismrhitl1($id_opt,$data)
	{
	   if($id_opt<>''){
	      return "<font color='green'><i>".$data."</i></font>";
	   }else{
	      return "$data";
	   }
	}
	
	function list_absperwalian($kd_fak,$kd_prodi,$thn_msk,$ta)
	{	
		$nm_stat = array(0=>"Non Aktif",1=>"Aktif",2=>"Lulus",3=>"Cuti",4=>"Keluar",5=>"Non Aktif");            
					
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."'");
					$vnm_prodi="";
					foreach ($data as $r){						
						  $vnm_prodi=$r['prodi'];						
					}
		$awl_form="<form name='absperwalian' id='absperwalian' method='post' >";
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat","width"=>"100%"));
		
		$tbl1->addRow();
        $tbl1->addCell('No.', null, 'header',array("align" => "center","valign"=>"middle"));	    
		$tbl1->addCell('Nama', null, 'header',array("align" => "center","valign"=>"middle"));
		$tbl1->addCell('NPM', null, 'header',array("align" => "center","valign"=>"middle"));	   
			   
		//$tbl1->addCell('Status', null, 'header',array("align" => "center","valign"=>"middle","colspan"=>"4"));
	    //$tbl1->addRow();     
		$tbl1->addCell('Status', null, 'header');
        
		
		$sql="";
		if($kd_fak<>""){
		  $sql="kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."' and verifikasi=1 and Tahun_masuk=".$thn_msk;
		}
				
		$data = $this->dt_mhs->getOrderedData($sql); 
		$dt_stat_mhs =  new dt_stat_mhs; 
		
		$txt="";
		$opt_ent=0;
	  if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  $i=$i+1;
		  if($row['optcid']<>"")
		  {
		   $opt_ent=1;
		  }
		  		  
		  $tbl1->addRow();        
		  $tbl1->addCell($this->ismrhitl1($row['optcid'],$i), null, 'data');
		  $tbl1->addCell($this->ismrhitl1($row['optcid'],$row['Nama_mahasiswa']), null, 'data');
		  $tbl1->addCell($this->ismrhitl1($row['optcid'],$row['NIM']), null, 'data');    
		  $idx_name = $row['NO_KTP'];
		  
		  $data_stat = $dt_stat_mhs->getData("thnsmsstat_mhs='".$ta."' and noktp_mhs='".$row['NO_KTP']."' and kd_fak='".$kd_fak."' and kd_prodi='".$kd_prodi."'");
		  $stat = 0;
		  if(!empty($data_stat))
          {  
		    foreach($data_stat as $row1)
		    {
		     $stat = $row1['statstat_mhs'];
		    }
		  }
		  						
		  $tbl1->addCell($nm_stat[$stat], null, 'data');  
		  
		}
		  
	   
      
	  }	   	 
	   
	   if($opt_ent==1)
	   {
	     $txt="<br>Keterangan : Data yang diwarnai di input oleh Operator.<br>".$awl_form.$tbl1->display("")."</form>";
	   }else{
	     $txt="<br>".$awl_form.$tbl1->display("")."</form>";
       }  

	   
	  
	   $html_txt="<fieldset>";
	   $html_txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend><div>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}
	
	function list_sbrnmtk($kd_fak,$kd_prodi,$ta)
	{	
		            $dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."'");
					$vnm_prodi="";
					foreach ($data as $r){						
						  $vnm_prodi=$r['prodi'];						
					}
		$awl_form="<form name='lstkrs' id='lstkrs' method='post' >";
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_sbrnmtk","width"=>"100%"));
		
		$tbl1->addRow();
        $tbl1->addCell('No.', null, 'header');	    
		$tbl1->addCell('Kode', null, 'header');
	    $tbl1->addCell('Nama', null, 'header');
		$tbl1->addCell('Semester', null, 'header');
		$tbl1->addCell('Reg./Non. Reg.', null, 'header');
		$tbl1->addCell('Kelas', null, 'header');			
        $tbl1->addCell('Jml mhs', null, 'header');	   
       	$tbl1->addCell('Kampus', null, 'header');	
		
		$sql="";
		if($kd_fak<>""){
		  $sql="kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."' and thsmskrs=".$ta;
		}
		        
		$dt_krs=new dt_krs;
		$data = $dt_krs->getMTK($sql); 		
			
		$txt="";
		$opt_ent=0;
	  if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		    $i=$i+1;
			$tbl1->addRow();        
		    $tbl1->addCell($i, null, 'data');
			$tbl1->addCell($row['kd_mk'], null, 'data');
			$tbl1->addCell($row['nm_mk'], null, 'data');
		    $tbl1->addCell($row['semkrs'], null, 'data');
		    $tbl1->addCell($row['shiftkrs'], null, 'data');
			$tbl1->addCell($row['kelaskrs'], null, 'data');						
		    $tbl1->addCell($row['jml_mhs'], null, 'data'); 		  
		 	$tbl1->addCell($row['kampus'], null, 'data');
		}
		     
	  }	   	 
	   
	  $txt="<br>".$awl_form.$tbl1->display("")."</form>";
         
	  
	   $html_txt="<fieldset>";
	   $html_txt.="<legend>Prodi : $vnm_prodi </legend><div>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}
	
	function list_krs($kd_fak,$kd_prodi,$thn_msk,$ta)
	{	
		            $dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."'");
					$vnm_prodi="";
					foreach ($data as $r){						
						  $vnm_prodi=$r['prodi'];						
					}
		$awl_form="<form name='lstkrs' id='lstkrs' method='post' >";
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_krs","width"=>"100%"));
		
		$tbl1->addRow();
        $tbl1->addCell('KTP', null, 'header',array("align" => "center","valign"=>"middle"));	    
		$tbl1->addCell('Nama', null, 'header',array("align" => "center","valign"=>"middle"));
		$tbl1->addCell('NPM', null, 'header',array("align" => "center","valign"=>"middle"));	   
		$tbl1->addCell('R/N', null, 'header',array("align" => "center","valign"=>"middle"));
        $tbl1->addCell('B/P', null, 'header',array("align" => "center","valign"=>"middle"));		
		  
		$tbl1->addCell('SKS', null, 'header');
        $tbl1->addCell('Aksi', null, 'header');	    
       			
		$sql="";
		if($kd_fak<>""){
		  $sql="kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."' and verifikasi=1 and Tahun_masuk=".$thn_msk;
		}
				
		$data = $this->dt_mhs->getOrderedData($sql); 
		$dt_jml_sks =  new dt_krs;		
		$txt="";
		$opt_ent=0;
	  if(!empty($data))
      {	 
		//$i=0;
		foreach($data as $row)
		{
		  //$i=$i+1;		  		  		  
		  $tbl1->addRow();        
		  $tbl1->addCell($row['NO_KTP'], null, 'data');
		  $tbl1->addCell($row['Nama_mahasiswa'], null, 'data');
		  $tbl1->addCell($row['NIM'], null, 'data');   
		  $tbl1->addCell($row['Kelas'], null, 'data'); 
		  $tbl1->addCell($row['Status_awal_mahasiswa'], null, 'data'); 
		  
          $data1=$dt_jml_sks->getMHS("NO_KTP='".$row['NO_KTP']."'");
		  $jmlsks=0;
		  if(!empty($data1))
          {
		    foreach($data1 as $row1)
		    {
			  $jmlsks=$row1['jml_sks'];
			}
		  }
		  $tbl1->addCell($jmlsks, null, 'data');
          
		  if($jmlsks==0){
		     $tbl1->addCell("", null, 'data');
		  }else{
		     $link1='javascript:viewkrs("'.$row['NO_KTP'].'")';
			  
			 $tbl1->addCell("<a href='".$link1."'>View</a>", null, 'data');
		  }
		  
		  //  		  
		 	  	  
		}
		     
	  }	   	 
	   
	  $txt="<br>".$awl_form.$tbl1->display("")."</form>";
         
	  
	   $html_txt="<fieldset>";
	   $html_txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend><div>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}
	
	
}
?>












