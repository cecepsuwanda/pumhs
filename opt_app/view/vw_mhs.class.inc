<?php
class vw_mhs
{  
    var $dt_mhs;
	var $arr_thn_msk;
	
	function __construct()
	{	  	
        $this->dt_mhs = new dt_mhs;	
        $this->arr_thn_msk=array();
        $tmp_date =date("Y");							
		for ($i=2006;$i<=$tmp_date;$i++){
		  $this->arr_thn_msk[$i]=$i;
		}
        		
	}
	
	function cekKTP($noktp)
	{ 	 
	 if ($this->dt_mhs->KTPada($noktp)=='1') {
	    return "<font size='1' color='red'>No KTP sudah ada dalam database !!!</font>"; 
	 }else{
	   return "<font size='1' color='green'>No KTP tidak ada dalam database !!!</font>";	 
	 }
	
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
		
		
		if ($proses==2){
		  $sql.="(verifikasi=1 or verifikasi=0) and ";
		}else{
		  $sql.="verifikasi=".$idx." and ";
		}
		
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
	
	function lst_entry_data1($fak="",$kd_prodi="",$id_opt="",$id="lst_mhs",$thn_msk=0)
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
		if(($fak<>"" and $kd_prodi<>"") or ($fak<>"" and $id_opt<>"")){
		  $sql="kd_fakultas='".$fak."' and ";
		}else {
		  $sql="kd_fakultas='".$fak."'";
		}
		
		if(($kd_prodi<>"" and $id_opt<>"") or ($kd_prodi<>"" and $thn_msk>0)){
		  $sql.="kd_prodi='".$kd_prodi."' and ";
		} else {
		  if($kd_prodi<>""){
		  $sql.="kd_prodi='".$kd_prodi."'";
		  }
		}	
		
		if($id_opt<>"" and $thn_msk>0){
		  $sql.="optcid='".$id_opt."' and Tahun_masuk=".$thn_msk;
		}else {
		  if($id_opt=="" and $thn_msk>0){
		    $sql.="(optcid is null or optcid='') and Tahun_masuk=".$thn_msk;
		  } else{
		    if($id_opt<>"" and $thn_msk==0){
		      $sql.="optcid='".$id_opt."'";
		    } 
		  }
		}

        //if($id_opt=="" and $thn_msk>0){
		//  $sql.="Tahun_masuk=".$thn_msk."";
		//}
		
			
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
	
	
	function entry_data($kd_prodi="",$id_opt="",$kd_fak="")
	{
        			
		    $txt='<div id="tabs">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Data Diinput Mahasiswa</a></li>';
			$txt.='<li><a href="#tabs-2">Data Diinput Operator</a></li>';
			$txt.='</ul>';
			$txt.='<div id="tabs-1">';						
			$txt.="<div>".$this->lst_entry_data1($kd_fak,$kd_prodi)."</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			if($id_opt<>""){	     
		       $link='javascript:inputdtmhs("'.$kd_fak.'","'.$kd_prodi.'");';
		       $txt.="<a href='".$link."'>Tambah Data</a><br>";
		       //$txt.="<a href='javascript:inputdtmhs();'>Tambah Data</a><br>";
		    }
			$txt.="<div>".$this->lst_entry_data1($kd_fak,$kd_prodi,$id_opt)."</div>";
			$txt.='</div>';
			
			$txt.='</div>';
			
	  return $txt;
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
		$tbl->addCell('Prodi', null, 'header');	    
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
		  $tbl->addCell($row['prodi'], null, 'data');         
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
							   $txt = $txt."<li>PUMHS tidak mengenali format no KTP anda, silakan hubungi operator untuk mengisi form PUMHS Off line !!!</li>";
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
						   if($row['verifikasi']==1){ 
							   if($this->dt_mhs->is_nim_double($row['NIM']))
							   {
								$txt .= "<li>NIM Double !!!</li>";
							   }
							   if($this->dt_mhs->is_nm_double($row['Nama_mahasiswa']))
							   {
								$txt .= "<li>Nama Double !!!</li>";
							   }
						   }
						}else{
						  if(($txt=="<li>NIM mohon diisi</li>") && (($row['NIM']=="") &&($row['Tahun_masuk']==2013)))
                          {
						     $this->dt_mhs->update_validasi($row['NO_KTP'],1);
							 
							   if($row['verifikasi']==1) {
								   if($this->dt_mhs->is_nm_double($row['Nama_mahasiswa']))
								   {
									$txt .= "<li>Nama Double !!!</li>";
								   }
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
	$tbl->addCell("Batas Studi", null, 'data');$tbl->addCell(":", null, 'data');$tbl->addCell($batasStudi, null, 'data');
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
	
	function input_data_mhs($kd_fak="",$kd_prod="")
	{
		
		
		$frm = new HTML_Form();
        $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));		
		$tbl->addRow();
        $tbl->addCell('<label>Nomor KTP <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"ktp","",array('id'=>'nomorKTP','maxlength'=>16,'size'=>16,'onkeypress'=>'return isNumberKey(event)','onblur'=>'return isKTPExist(event)'))."<div id='ktpada' ></div>", null, 'data');
		$tbl->addRow();
        $tbl->addCell('<label for="nim">Nomor Pokok Mahasiswa </label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"nim","",array('id'=>'nim','maxlength'=>9)), null, 'data');
        $tbl->addRow();
		$tbl->addCell('<label for="namaMahasiswa" class="required">Nama Mahasiswa <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"namaMahasiswa","",array('id'=>'namaMahasiswa','maxlength'=>30)), null, 'data');
        $tbl->addRow();
		$tbl->addCell('<label for="tempatLahir" class="required">Tempat Lahir <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"tempatLahir","",array('id'=>'tempatLahir','maxlength'=>20)), null, 'data');
		$tbl->addRow();
		$tbl->addCell('<label for="tanggalLahir" class="required">Tanggal Lahir <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"tanggalLahir","",array('id'=>'tanggalLahir','onchange'=>"checkKTP()")), null, 'data');
		$tbl->addRow();
		$tbl->addCell('<label for="jenisKelamin" class="required">Jenis Kelamin <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addSelectList("jenisKelamin",array('P'=>'Perempuan','L'=>'Laki-laki'),true,null,null,array('id'=>'jenisKelamin')), null, 'data');
		$tbl->addRow();
        $tbl->addCell('<label for="alamat" class="required">Alamat <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell('<textarea name="alamat" id="alamat" maxlength="100" ></textarea>', null, 'data');		
		$tbl->addRow();
        $tbl->addCell('<label for="kota" class="required">Kabupaten / Kota <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addSelectList("kota",array(''=>'','121451'=>'Kota Bandung','121452'=>'Kabupaten Bandung','121453'=>'Kota Cimahi','121454'=>'Kabupaten Sumedang','121455'=>'Kabupaten Cianjur'),true,null,null,array('id'=>'kota')), null, 'data');		
		$tbl->addRow();
        $tbl->addCell('<label for="provinsi" class="required">Provinsi <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addSelectList("provinsi",array(''=>'','121'=>'Jawa Barat','122'=>'Jawa Tengah','123'=>'Jawa Timur','124'=>'DI Jogjakarta','125'=>'DKI Jakarta'),true,null,null,array('id'=>'provinsi')), null, 'data');		
		$tbl->addRow();
		$tbl->addCell('<label for="kodePos" >Kode Pos </label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"kodePos","",array('id'=>'kodePos','maxlength'=>10)), null, 'data');
		
		$tbl->addRow();
		$tbl->addCell('<label for="telepon" >Telepon </label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"telepon","",array('id'=>'telepon','maxlength'=>"20",'onkeypress'=>"return isNumberKey(event)")), null, 'data');
		$tbl->addRow();
		$tbl->addCell('<label for="hp" >No. HP </label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"hp","",array('id'=>'hp','maxlength'=>"20",'onkeypress'=>"return isNumberKey(event)")), null, 'data');
		
		$tbl->addRow();
		$tbl->addCell('Fakultas dan Prodi', null, 'data');
	    $tbl->addCell(':', null, 'data');	
			
            
                $txt='<select name="Prodi" id="Prodi" data-placeholder=" pilih program studi asal...">';

					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$txt.= "<option selected='selected' value=''></option> ";
					foreach ($data as $r){
						$txt.="<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>
						";
					}

                 $txt.='</select>';
        $tbl->addCell($txt, null, 'data'); 
		
		$tbl->addRow();
		$tbl->addCell('<label for="tanggalMasuk" class="required">Tanggal Masuk <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"tanggalMasuk","2008-09-05",array('id'=>'tanggalMasuk','onchange'=>"thnMasuk()")), null, 'data');	
		$tbl->addRow();
	    $tbl->addCell('Tahun Masuk', null, 'data');
	    $tbl->addCell(':', null, 'data');		
		$tbl->addCell($frm->addSelectList("tahunMasuk",$this->arr_thn_msk,true,2008,null,array('id'=>'tahunMasuk')), null, 'data');		
		$tbl->addRow();
		$tbl->addCell('<label for="batasStudi">Batas Studi</label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"batasStudi","2015",array('id'=>'batasStudi','maxlength'=>5)), null, 'data');	
		$tbl->addRow();
	    $tbl->addCell('<label for="statusMahasiswa" class="required">Status Mahasiswa <span class="required">*</span></label>', null, 'data');
	    $tbl->addCell(':', null, 'data');
	    $tbl->addCell($frm->addSelectList("statusMahasiswa",array('A'=>'Aktif','C'=>'Cuti','L'=>'Lulus'),true,"A",null,array('id'=>'statusMahasiswa')), null, 'data');
		
		$tbl->addRow();
	    $tbl->addCell('Kelas', null, 'data');
	    $tbl->addCell(':', null, 'data');
	    $tbl->addCell($frm->addSelectList("kelas",array('R'=>'Reguler','N'=>'Non Reguler'),true,"R",null,array('id'=>'kelas')), null, 'data');
		$tbl->addRow();
	    $tbl->addCell('Status Awal Mahasiswa', null, 'data');
	    $tbl->addCell(':', null, 'data');
	    $tbl->addCell($frm->addSelectList("statusAwalMahasiswa",array('B'=>'Baru','P'=>'Pindahan'),true,"B",null,array('id'=>'statusAwalMahasiswa')), null, 'data');
		
		
		$tbl4 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));
		$tbl4->addRow();
		$tbl4->addCell('Status Kerja', null, 'data');
		$tbl4->addCell(':', null, 'data');
		$tbl4->addCell($frm->addSelectList("kodePekerjaan",array('J'=>'Belum bekerja','G'=>'Pegawai Swasta','I'=>'Wiraswasta','H'=>'LSM','E'=>'PNS Lembaga Pemerintahan','K'=>'Guru Honor','D'=>'Dosen PTS','C'=>'Dosen DPK PTS','B'=>'Dosen kontrak PTN/ BHMN','A'=>'Dosen PNS PTN/ BHMN','F'=>'TNI/POLRI'),true,null,null,array('id'=>'kodePekerjaan')), null, 'data');
		$tbl4->addRow();
	    $tbl4->addCell('<label for="namaTempatPekerjaan">Nama Tempat Bekerja </label>', null, 'data');
	    $tbl4->addCell(':', null, 'data');
	    $tbl4->addCell('<textarea name="namaTempatPekerjaan" id="namaTempatPekerjaan" maxlength="40" ></textarea>', null, 'data');
	  	
		
		
		
		$tbl2 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));		 
		 
		$tbl2->addRow();
		$tbl2->addCell('<label for="smaAsal" class="required">SMA Asal <span class="required">*</span></label>', null, 'data');
		$tbl2->addCell(':', null, 'data');
		$tbl2->addCell($frm->addInput('text',"smaAsal","",array('id'=>'smaAsal','maxlength'=>"40")), null, 'data');	
          
		
		$tbl5 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));
		$tbl5->addRow();
		$tbl5->addCell('<label for="tanggalLulus" class="required" >Tanggal Lulus </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"tanggalLulus","0000-00-00",array('id'=>'tanggalLulus')), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="ipkAkhir">IPK Akhir </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"ipkAkhir","0.00",array('id'=>'ipkAkhir','maxlength'=>4)), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="nomorSkYudisium">Nomor SK Yudisium </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"nomorSkYudisium","",array('id'=>'nomorSkYudisium','maxlength'=>30)), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="tanggalYudisium" class="required">Tanggal Yudisium </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"tanggalYudisium","0000-00-00",array('id'=>'tanggalYudisium')), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="nomorSeriIjazah">Nomor Seri Ijazah </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"nomorSeriIjazah","",array('id'=>'nomorSeriIjazah','maxlength'=>40)), null, 'data');	
		
		
		
		$tbl3 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));
		$tbl3->addRow();
		$tbl3->addCell('Perguruan Tinggi Asal', null, 'data');
	    $tbl3->addCell(':', null, 'data');
			
			 
                $txt='<select name="universitasAsal" id="universitasAsal" data-placeholder=" pilih perguruan tinggi asal...">';
				

					$dt_universitas=new dt_universitas;
					$data = $dt_universitas->getData("");
					$txt.= "<option selected='selected' value=''></option> ";
					foreach($data as $r){
				      $txt.= "<option value=".$r['Kode_Univ'].">".$r['Nama_Univ']." </option>
					  ";
				}

               $txt.='</select>';
         $tbl3->addCell($txt, null, 'data'); 
		 $tbl3->addRow();
	     $tbl3->addCell('Fakultas dan Prodi asal', null, 'data');
	     $tbl3->addCell(':', null, 'data');
	             $txt='<select name="prodiAsal" id="prodiAsal" data-placeholder=" pilih program studi asal...">';

					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");
					$txt.= "<option selected='selected' value=''></option> ";
					foreach ($data as $r){
						$txt.="<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>
						";
					}

                 $txt.='</select>';
           
		  $tbl3->addCell($txt, null, 'data');		
			
			
			$tbl3->addRow();
		    $tbl3->addCell('<label for="sksDiakui">Jumlah SKS diakui </label>', null, 'data');
		    $tbl3->addCell(':', null, 'data');
		    $tbl3->addCell($frm->addInput('text',"sksDiakui","0",array('id'=>'sksDiakui','maxlength'=>3)), null, 'data');	
			
			
			
		    $tbutton=$frm->addInput('button',"save","save",array('onclick'=>'cekform(1)'));
			
			
			$txt2="<BR><center><H1>BIODATA MAHASISWA</H1></center><BR>";
			
			$txt2.="<ol>";
			$txt2.="<li>Data Mahasiswa<br><br>".$tbl->display('')."<br></li>";
			$txt2.="<li>Data Asal SMA/SMK/MA/Sederajat<br><br>".$tbl2->display('')."<br></li>";
			$txt2.="<li>Data Perguruan Tinggi Asal (diisi oleh mahasiswa pindahan atau lanjutan)<br><br>".$tbl3->display('')."<br></li>";
			$txt2.="<li>Informasi Pekerjaan(diisi oleh mahasiswa yang sudah bekerja)<br><br>".$tbl4->display('')."<br></li>";
			$txt2.="<li>Informasi Kelulusan(diisi oleh mahasiswa yang sudah lulus)<br><br>".$tbl5->display('')."<br></li>";
			$txt2.="</ol>";
			
			//$txt2.=$tbl->display("")."<BR>";
			//$txt2.=$tbl1->display("")."<BR>";
			
            			
		return $frm->startForm(null,'post','input-form').$txt2.$tbutton.$frm->endForm();	 
	
	}
	
	function filter_list_mhs($fak="",$id_opt="",$kd_prodi,$thn_msk)
    {
	   $dt_prodi=new dt_prodi;
	   $data = $dt_prodi->getData("kd_fakultas='".$fak."' and kd_prodi='".$kd_prodi."'");
	   foreach ($data as $r){
	     $vnm_prodi=$r['prodi'];    
	   }
	   
	   $txt= "<fieldset>";
	   $txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend>";
       	$txt.='<div id="tabs">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Data Diinput Mahasiswa</a></li>';
			$txt.='<li><a href="#tabs-2">Data Diinput Operator</a></li>';
			$txt.='</ul>';
			$txt.='<div id="tabs-1">';						
			$txt.="<div>".$this->lst_entry_data1($fak,$kd_prodi,"","lstmhs1",$thn_msk)."</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			if($id_opt<>""){	     
		       $link='javascript:inputdtmhs("'.$fak.'","'.$kd_prodi.'");';
		       $txt.="<a href='".$link."'>Tambah Data</a><br>";
		       //$txt.="<a href='javascript:inputdtmhs();'>Tambah Data</a><br>";
		    }
			 $txt.="<div>".$this->lst_entry_data1($fak,$kd_prodi,$id_opt,"lstmhs2",$thn_msk)."</div>";
			$txt.='</div>';
			
			$txt.='</div>';
	  $txt.="</fieldset><br>";
	  return $txt;  
	}	
	
	
	function list_mhs($fak="",$id_opt="")
	{
	                $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
	  $tmp='"'.$fak.'"';
	  $txt = "<fieldset>";
	  $txt=$txt."<legend>Filter: </legend>";	  
	  $txt_prodi='<select name="Prodi_hsl_val" id="Prodi_hsl_val">'.$txt1.'</select>';
	  $txt_angkatan='<select name="thn_hsl_val" id="thn_hsl_val">'.$txt2.'</select>';
	  $frm = new HTML_Form();
	  $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_list_mhs('".$fak."')"))."<button onclick='cetak_data(".$tmp.")'>Cetak Data</button>";
	  $txt.="</fieldset>";

	  $txt.="<div id = 'data_list_mhs'>";
	  $txt.=$this->filter_list_mhs($fak,$id_opt,$vkd_prodi,$thn_msk);
	  $txt.="</div>";
	  		
	  return $txt; 
	  
	}
	
	function edit_data_mhs($ktp,$kd_fak)
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
			
		
		
		
		$frm = new HTML_Form();
        $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));				
		$tbl->addRow();
        $tbl->addCell('<label>Nomor KTP <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"ktp","$ktp",array('id'=>'ktp','maxlength'=>16,'size'=>16,'onkeypress'=>'return isNumberKey(event)','readonly'=>'readonly','disabled'=>'disabled')).$frm->addInput('hidden',"ktp",$ktp,null), null, 'data');
		$tbl->addRow();
        $tbl->addCell('<label for="nim">Nomor Pokok Mahasiswa </label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"nim","$nim",array('id'=>'nim','maxlength'=>9)), null, 'data');
        $tbl->addRow();
		$tbl->addCell('<label for="namaMahasiswa" class="required">Nama Mahasiswa <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"namaMahasiswa","$Nama_mahasiswa",array('id'=>'namaMahasiswa','maxlength'=>30)), null, 'data');
        $tbl->addRow();
		$tbl->addCell('<label for="tempatLahir" class="required">Tempat Lahir <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"tempatLahir","$tempatLahir",array('id'=>'tempatLahir','maxlength'=>20)), null, 'data');
		$tbl->addRow();
		$tbl->addCell('<label for="tanggalLahir" class="required">Tanggal Lahir <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"tanggalLahir","$tanggalLahir",array('id'=>'tanggalLahir','onchange'=>"checkKTP()")), null, 'data');
		$tbl->addRow();
		$tbl->addCell('<label for="jenisKelamin" class="required">Jenis Kelamin <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addSelectList("jenisKelamin",array('P'=>'Perempuan','L'=>'Laki-laki'),true,$jenisKelamin,null,array('id'=>'jenisKelamin')), null, 'data');
		$tbl->addRow();
        $tbl->addCell('<label for="alamat" class="required">Alamat <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell('<textarea name="alamat" id="alamat" maxlength="100" >'.$alamat.'</textarea>', null, 'data');		
		$tbl->addRow();
        $tbl->addCell('<label for="kota" class="required">Kabupaten / Kota <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addSelectList("kota",array(''=>'','121451'=>'Kota Bandung','121452'=>'Kabupaten Bandung','121453'=>'Kota Cimahi','121454'=>'Kabupaten Sumedang','121455'=>'Kabupaten Cianjur'),true,intval($kota),null,array('id'=>'kota')), null, 'data');		
		$tbl->addRow();
        $tbl->addCell('<label for="provinsi" class="required">Provinsi <span class="required">*</span></label>', null, 'data');
        $tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addSelectList("provinsi",array(''=>'','121'=>'Jawa Barat','122'=>'Jawa Tengah','123'=>'Jawa Timur','124'=>'DI Jogjakarta','125'=>'DKI Jakarta'),true,intval($provinsi),null,array('id'=>'provinsi')), null, 'data');		
		$tbl->addRow();
		$tbl->addCell('<label for="kodePos" >Kode Pos </label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"kodePos","$kodePos",array('id'=>'kodePos','maxlength'=>10)), null, 'data');
		$tbl->addRow();
		$tbl->addCell('<label for="telepon" class="required">Telepon</label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"telepon","$telepon",array('id'=>'telepon','maxlength'=>"20",'onkeypress'=>"return isNumberKey(event)")), null, 'data');
		$tbl->addRow();
		$tbl->addCell('<label for="hp" class="required">No. HP </label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"hp","$hp",array('id'=>'hp','maxlength'=>"20",'onkeypress'=>"return isNumberKey(event)")), null, 'data');
	    $tbl->addRow();
		$tbl->addCell('Fakultas dan Prodi', null, 'data');
	    $tbl->addCell(':', null, 'data');	
			
            
                $txt='<select name="Prodi" id="Prodi" data-placeholder=" pilih program studi asal...">';

					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$txt.= "<option selected='selected' value=''></option> ";
					foreach ($data as $r){
						$txt.= "<option ";
						if ($prod == $r['kd_prodi']) $txt.= "selected='selected' ";
						$txt.= "value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>
						";
					}

                 $txt.='</select>';
            $tbl->addCell($txt, null, 'data'); 
		
		
		
		$tbl->addRow();
	    $tbl->addCell('Kelas', null, 'data');
	    $tbl->addCell(':', null, 'data');
	    $tbl->addCell($frm->addSelectList("kelas",array('R'=>'Reguler','N'=>'Non Reguler'),true,$kelas,null,array('id'=>'kelas')), null, 'data');
        $tbl->addRow();
		$tbl->addCell('<label for="tanggalMasuk" class="required">Tanggal Masuk <span class="required">*</span></label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"tanggalMasuk","$tanggalMasuk",array('id'=>'tanggalMasuk','onchange'=>"thnMasuk()")), null, 'data');	
		$tbl->addRow();
	    $tbl->addCell('Tahun Masuk', null, 'data');
	    $tbl->addCell(':', null, 'data');
	    $tbl->addCell($frm->addSelectList("tahunMasuk",$this->arr_thn_msk,true,intval($tahunMasuk),null,array('id'=>'tahunMasuk')), null, 'data');		
		$tbl->addRow();
		$tbl->addCell('<label for="batasStudi">Batas Studi </label>', null, 'data');
		$tbl->addCell(':', null, 'data');
		$tbl->addCell($frm->addInput('text',"batasStudi","$batasStudi",array('id'=>'batasStudi','maxlength'=>5)), null, 'data');	
	  	$tbl->addRow();
	    $tbl->addCell('<label for="statusMahasiswa" class="required">Status Mahasiswa <span class="required">*</span></label>', null, 'data');
	    $tbl->addCell(':', null, 'data');
	    $tbl->addCell($frm->addSelectList("statusMahasiswa",array('A'=>'Aktif','C'=>'Cuti','L'=>'Lulus'),true,$status,null,array('id'=>'statusMahasiswa')), null, 'data');
		$tbl->addRow();
	    $tbl->addCell('Status Awal Mahasiswa', null, 'data');
	    $tbl->addCell(':', null, 'data');
	    $tbl->addCell($frm->addSelectList("statusAwalMahasiswa",array('B'=>'Baru','P'=>'Pindahan'),true,$status_awl,null,array('id'=>'statusAwalMahasiswa')), null, 'data');  
		
		$tbl4 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));
		$tbl4->addRow();
		$tbl4->addCell('Status Kerja', null, 'data');
		$tbl4->addCell(':', null, 'data');
		$tbl4->addCell($frm->addSelectList("kodePekerjaan",array('J'=>'Belum bekerja','G'=>'Pegawai Swasta','I'=>'Wiraswasta','H'=>'LSM','E'=>'PNS Lembaga Pemerintahan','K'=>'Guru Honor','D'=>'Dosen PTS','C'=>'Dosen DPK PTS','B'=>'Dosen kontrak PTN/ BHMN','A'=>'Dosen PNS PTN/ BHMN','F'=>'TNI/POLRI'),true,$kodePekerjaan,null,array('id'=>'kodePekerjaan')), null, 'data');
		$tbl4->addRow();
	    $tbl4->addCell('<label for="namaTempatPekerjaan">Nama Tempat Bekerja </label>', null, 'data');
	    $tbl4->addCell(':', null, 'data');
	    $tbl4->addCell('<textarea name="namaTempatPekerjaan" id="namaTempatPekerjaan" maxlength="40" >'.$namaTempatPekerjaan.'</textarea>', null, 'data');
		
		
		
		 
		$tbl2 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));
		$tbl2->addRow();
		$tbl2->addCell('<label for="smaAsal" class="required">SMA Asal <span class="required">*</span></label>', null, 'data');
		$tbl2->addCell(':', null, 'data');
		$tbl2->addCell($frm->addInput('text',"smaAsal","$smaAsal",array('id'=>'smaAsal','maxlength'=>"40")), null, 'data');	
        
		$tbl5 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));
		$tbl5->addRow();
		$tbl5->addCell('<label for="tanggalLulus" class="required" >Tanggal Lulus </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"tanggalLulus","$tanggalLulus",array('id'=>'tanggalLulus')), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="ipkAkhir">IPK Akhir </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"ipkAkhir","$ipkAkhir",array('id'=>'ipkAkhir','maxlength'=>4)), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="nomorSkYudisium">Nomor SK Yudisium </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"nomorSkYudisium","$nomorSkYudisium",array('id'=>'nomorSkYudisium','maxlength'=>30)), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="tanggalYudisium" class="required">Tanggal Yudisium </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"tanggalYudisium","$tanggalYudisium",array('id'=>'tanggalYudisium')), null, 'data');	
		$tbl5->addRow();
		$tbl5->addCell('<label for="nomorSeriIjazah">Nomor Seri Ijazah </label>', null, 'data');
		$tbl5->addCell(':', null, 'data');
		$tbl5->addCell($frm->addInput('text',"nomorSeriIjazah","$nomorSeriIjazah",array('id'=>'nomorSeriIjazah','maxlength'=>40)), null, 'data');	
		
		$tbl3 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "dt_mhs","width"=>"100%"));
		$tbl3->addRow();
		$tbl3->addCell('Perguruan Tinggi Asal', null, 'data');
	    $tbl3->addCell(':', null, 'data');
			
			 
                $txt='<select name="universitasAsal" id="universitasAsal" data-placeholder=" pilih perguruan tinggi asal...">';
				

					$dt_universitas=new dt_universitas;
					$data = $dt_universitas->getData("");
					$txt.= "<option selected='selected' value=''></option> ";
					foreach($data as $r){
				      $txt.= "<option ";
					  if ($universitasAsal==$r['Kode_Univ']) $txt.= "selected ";
					  $txt.= "value=".$r['Kode_Univ'].">".$r['Nama_Univ']." </option>
					  ";
				    }

               $txt.='</select>';
         $tbl3->addCell($txt, null, 'data'); 
		 $tbl3->addRow();
	     $tbl3->addCell('Fakultas dan Prodi asal', null, 'data');
	     $tbl3->addCell(':', null, 'data');
	             $txt='<select name="prodiAsal" id="prodiAsal" data-placeholder=" pilih program studi asal...">';

					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");
					$txt.= "<option selected='selected' value=''></option> ";
					foreach ($data as $r){
						$txt.= "<option "; 
						if ($prodiAsal==$r['kd_prodi']) $txt.= "selected ";
						$txt.= "value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>
						";
					}

                 $txt.='</select>';
           
		$tbl3->addCell($txt, null, 'data');		
			
			$tbl3->addRow();
		    $tbl3->addCell('<label for="sksDiakui">Jumlah SKS diakui </label>', null, 'data');
		    $tbl3->addCell(':', null, 'data');
		    $tbl3->addCell($frm->addInput('text',"sksDiakui","$sksDiakui",array('id'=>'sksDiakui','maxlength'=>3)), null, 'data');	
			
			
			
			
			$tbutton=$frm->addInput('button',"save","save",array('onclick'=>'cekform(2)'));
		    
            
			$txt2="<BR><center><H1>BIODATA MAHASISWA</H1></center><BR>";
			
			$txt2.="<ol>";
			$txt2.="<li>Data Mahasiswa<br><br>".$tbl->display('')."<br></li>";
			$txt2.="<li>Data Asal SMA/SMK/MA/Sederajat<br><br>".$tbl2->display('')."<br></li>";
			$txt2.="<li>Data Perguruan Tinggi Asal (diisi oleh mahasiswa pindahan atau lanjutan)<br><br>".$tbl3->display('')."<br></li>";
			$txt2.="<li>Informasi Pekerjaan(diisi oleh mahasiswa yang sudah bekerja)<br><br>".$tbl4->display('')."<br></li>";
			$txt2.="<li>Informasi Kelulusan(diisi oleh mahasiswa yang sudah lulus)<br><br>".$tbl5->display('')."<br></li>";
			$txt2.="</ol>";
			
			
			//$txt2=$tbl->display("")."<BR>";
			//$txt2.=$tbl1->display("")."<BR>";
			
            
			
		return $frm->startForm(null,'post','editmhs').$txt2.$tbutton.$frm->endForm();	 
	
	}	
	
	// amip 20131230 02:36 
	function filter_verifikasi($kd_fak)
	{
	  
      //$tbl->addCell('Nama File '.$txt.' '.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."')")), null, 'data');	  
      //$html_txt.=$this->list_verifikasi_mhs($kd_fak,$vnm_file);
	    		 
	              
			        $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
					
					$txt3="";
					$dt_mhs=new dt_mhs;
					$data = $dt_mhs->get_nm_file('kd_fakultas="'.$kd_fak.'"');
					
					$nm_file="";
					foreach ($data as $r){
						$nm_file1='"'.$r['nm_file'].'"';
						if($nm_file=="")
						{
						  
						  $nm_file=$r['nm_file'];						  
						  $txt3.= "<option selected='selected' value=".$nm_file1.">".$r['nm_file']."  (".$r['jml_ver']."/".$r['jml'].")"."</option>";
						}
						else{
						$txt3.= "<option value=".$nm_file1.">".$r['nm_file']."  (".$r['jml_ver']."/".$r['jml'].")"."</option>";
						}
					}
					
      
	  
	  	
            $tmp='"'.$kd_fak.'"';
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
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."',1)"))."<button onclick='cetak_blmlyk_verifikasi(".$tmp.")'>Cetak Belum Layak Verfikasi</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_blm_lyk'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,1);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_prodi='<select name="Prodi_frm_ver" id="Prodi_frm_ver">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_frm_ver" id="thn_frm_ver">'.$txt2.'</select>';	  
	        $frm = new HTML_Form();
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."',2)"))."<button onclick='cetak_frm_verifikasi(".$tmp.")'>Cetak Form Verfikasi</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_lyk'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,2);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-3">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_prodi='<select name="Prodi_hsl_ver" id="Prodi_hsl_ver">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_hsl_ver" id="thn_hsl_ver">'.$txt2.'</select>';	  
	        $frm = new HTML_Form();
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."',3)"))."<button onclick='cetak_hsl_verifikasi(".$tmp.")'>Cetak Hasil Verfikasi</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_lls'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,3);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-4">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        $txt_prodi='<select name="Prodi_tlls" id="Prodi_tlls">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_tlls" id="thn_tlls">'.$txt2.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."',4)"));
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_tlls'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,4);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='<div id="tabs-5">';
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";	  
	        //$txt_prodi='<select name="Prodi_sdver" id="Prodi_sdver">'.$txt1.'</select>';
	        //$txt_angkatan='<select name="thn_sdver" id="thn_sdver">'.$txt2.'</select>';	 
			$txt_nmfile='<select name="nmfile" id="nmfile">'.$txt3.'</select>';
			$frm = new HTML_Form();
	        //$txt.= "Prodi ".$txt_prodi."Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."',5)"));
			$txt.= "Nama File ".$txt_nmfile.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_verifikasi('".$kd_fak."',5)"));
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_sdver'>";
			//$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,5);
			$txt.=$this->list_verifikasi_mhs($kd_fak,$nm_file);
			$txt.="</div>";
			$txt.='</div>';
			$txt.='</div>';				 
	  
	  
	  //$txt.="</fieldset>";
	  return $txt;
	}
	
	function hsl_filter($kd_fak="",$kd_prodi="",$thn_msk=0,$idx,$nmfile="",$ta=0)
	{
	   
	 if($idx!=5 and $idx!=6 and $idx!=7 and $idx!=8 and $idx!=9 and $idx!=10 and $idx!=11){
       $dt_prodi=new dt_prodi;
	   $data = $dt_prodi->getData("kd_fakultas='".$kd_fak."' and kd_prodi='".$kd_prodi."'");
	   foreach ($data as $r){
	     $vnm_prodi=$r['prodi'];    
	   }
	  
	   $txt= "<fieldset>";
	   $txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend><div>";
	 } 
	 switch($idx)
     { 	 
	  case 1 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",0,"lst_mhs1",1,$thn_msk); break;
      case 2 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",0,"lst_mhs2",2,$thn_msk,2); break;
	  //case 5 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",0,"lst_mhs5",2,$thn_msk,1); break;
      case 5 : $txt=$this->list_verifikasi_mhs($kd_fak,$nmfile); break;
	  case 3 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",1,"lst_mhs3",0,$thn_msk); break;
	  case 4 : $txt.=$this->lst_entry_data($kd_fak,$kd_prodi,"",2,"lst_mhs4",0,$thn_msk); break;
	  case 6 : $txt=$this->list_absperwalian($kd_fak,$kd_prodi,$thn_msk,$ta); break;
	  case 7 : $txt=$this->list_krs($kd_fak,$kd_prodi,$thn_msk,$ta); break;
	  case 8 : $txt=$this->list_sbrnmtk($kd_fak,$kd_prodi,$ta); break;
	  case 9 : $txt=$this->list_nilai($kd_fak,$kd_prodi,$ta); break;
	  case 10 : $txt=$this->list_khs($kd_fak,$kd_prodi,$thn_msk,$ta); break;
	  case 11 : $txt=$this->list_kur($kd_fak,$kd_prodi,$ta); break;

	 } 
	if($idx!=5 and $idx!=6 and $idx!=7 and $idx!=8 and $idx!=9 and $idx!=10 and $idx!=11){ 
	 $txt.= "</div></fieldset>";
	} 
	  
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
	
	function list_verifikasi_mhs($fak="",$nm_file)
	{	
		
		$awl_form="<form name='verifikasi' id='verifikasi' method='post' >";
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs5","width"=>"100%"));
		
		$tbl1->addRow();
                $tbl1->addCell('No.', null, 'header');	    
		$tbl1->addCell('Nama', null, 'header');
		$tbl1->addCell('NPM', null, 'header');	   
		
	        $tbl1->addCell('Alamat', null, 'header');      
		$tbl1->addCell('Terverifikasi', null, 'header');	    
       	        $tbl1->addCell('Tidak Terverifikasi', null, 'header');
		
		$sql="";
		if($fak<>""){
		  $sql="kd_fakultas='".$fak."' and nm_file='".$nm_file."'";
		}
				
		$data = $this->dt_mhs->getOrderedData($sql); 
		$txt="";
		$opt_ent=0;
		if(!empty($data) and $nm_file!="")
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
		  $tbl1->addCell($this->ismrhitl1($row['optcid'],$row['Alamat']), null, 'data');
		  $idx_name = $row['NO_KTP'];
		  
		  switch($row['verifikasi'])
          {
            case 0 : $Kchek1='';
			         $Kchek2='';
			         break;
			case 1 : $Kchek1='checked';
			         $Kchek2='';
			         break;
            case 2 : $Kchek1='';
			         $Kchek2='checked';
			         break;					 
          } 		  
			$txt_checkbox1 = "<input type='radio' name='ver[$idx_name]' value='1' $Kchek1>";
		  
		    $txt_checkbox2 = "<input type='radio' name='ver[$idx_name]' value='2' $Kchek2>";
		  
		  $tbl1->addCell($txt_checkbox1, null, 'data');  
		  $tbl1->addCell($txt_checkbox2, null, 'data');
		}
		  
	   
      
	  }	   	 
	   
	   if($opt_ent==1)
	   {
	     $txt="<br>Keterangan : Data yang diwarnai di input oleh Operator.<br>".$awl_form.$tbl1->display("")."</form>";
	   }else{
	     $txt="<br>".$awl_form.$tbl1->display("")."</form>";
       }  

	   
	  if(!empty($data) and $nm_file!="")
      { 	
	   $tmp_text="save_verifikasi('".$fak."','".$nm_file."')";
	   $txt.='<br><input type="submit" value="Save" onclick="'.$tmp_text.'">';
	   
	  }
	   $html_txt="<fieldset>";
	   $html_txt.="<legend  id='hsl_filter'>Nama File : ".$nm_file."</legend>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}
	
	function list_absperwalian($kd_fak,$kd_prodi,$thn_msk,$ta)
	{	
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);
					
		$awl_form="<form name='absperwalian' id='absperwalian' method='post' >";
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_stat","width"=>"100%"));
		
		$tbl1->addRow();
        $tbl1->addCell('No.', null, 'header',array("align" => "center","valign"=>"middle"));	    
		$tbl1->addCell('Nama', null, 'header',array("align" => "center","valign"=>"middle"));
		$tbl1->addCell('NPM', null, 'header',array("align" => "center","valign"=>"middle"));	   
			   
		//$tbl1->addCell('Status', null, 'header',array("align" => "center","valign"=>"middle","colspan"=>"4"));
	    //$tbl1->addRow();     
		$tbl1->addCell('Aktif', null, 'header');
        $tbl1->addCell('Lulus', null, 'header');	    
       	$tbl1->addCell('Cuti', null, 'header');
		$tbl1->addCell('Keluar', null, 'header');
		$tbl1->addCell('Non Aktif', null, 'header');
		
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
		  $stat = !empty($data_stat) ? $data_stat[0]['statstat_mhs'] : 0 ;		    
		  		  
		  for($j=0;$j<=5;$j++){
		    $arr_chek[$j]='';
		  }

          $arr_chek[$stat]='checked';
		  	
		  for($j=1;$j<=5;$j++){		  
		    $txt_checkbox = "<input type='radio' name='ver[$idx_name]' value='$j' ".$arr_chek[$j].">";		  
		    $tbl1->addCell($txt_checkbox, null, 'data');  
		   }  
		  
		}	   
      
	  }	   	 
	   
	   $txt="<br>";	   
	   $txt.=($opt_ent==1) ? "Keterangan : Data yang diwarnai di input oleh Operator." : "";
	   $txt.="<br>".$awl_form.$tbl1->display("")."</form>";
	   
	  if(!empty($data))
      { 	
	   $tmp_text="save_absperwalian('".$kd_fak."','".$kd_prodi."',".$ta.")";
	   $txt.='<br><input type="submit" value="Save" onclick="'.$tmp_text.'">';
	   
	  }
	   $html_txt="<fieldset>";
	   $html_txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend><div>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}

	function list_kur($kd_fak,$kd_prodi,$ta)
	{	
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);
		
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_kur","width"=>"100%"));
		
		$tbl1->addRow();
        $tbl1->addCell('No.', null, 'header');	    
		$tbl1->addCell('Sem.', null, 'header');
		$tbl1->addCell('Kode', null, 'header');
	    $tbl1->addCell('Nama', null, 'header');
		$tbl1->addCell('SKS', null, 'header');
		$tbl1->addCell('KRS', null, 'header');
		$tbl1->addCell('Mtk. Prak.', null, 'header');
		$tbl1->addCell('Prak.', null, 'header');			
        
		
		$sql="";
		if($kd_fak<>""){
		  $sql="fak='".$kd_fak."' and prodi='".$kd_prodi."' and thn_sms=".$ta;
		}
		        
		$dt_mtk=new dt_mtk;
		$data = $dt_mtk->getData($sql); 		
			
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
			$tbl1->addCell($row['sem'], null, 'data');
			$tbl1->addCell($row['kd_mk'], null, 'data');
			$tbl1->addCell($row['nm_mk'], null, 'data');
		    $tbl1->addCell($row['sks_tot'], null, 'data');
		    $tbl1->addCell($row['flag_krs']==1 ? 'Yes' :'', null, 'data');
			$tbl1->addCell($row['flag_p']==1 ? 'Yes' :'', null, 'data');
			$tbl1->addCell($row['kd_lab'], null, 'data');						
		    
		}
		     
	  }	   	 
	   
	  $txt=$tbl1->display("");
         
	  
	   $html_txt="<fieldset>";
	   $html_txt.="<legend>Prodi : $vnm_prodi </legend><div>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}

	function list_nilai($kd_fak,$kd_prodi,$ta)
	{	
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);

		$awl_form="<form name='lstkrs' id='lstkrs' method='post' >";
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_nilai","width"=>"100%"));
		
		$tbl1->addRow();
        $tbl1->addCell('No.', null, 'header');	    
		$tbl1->addCell('Kode', null, 'header');
	    $tbl1->addCell('Nama', null, 'header');
		$tbl1->addCell('Sem.', null, 'header');
		$tbl1->addCell('R/N', null, 'header');
		$tbl1->addCell('Kelas', null, 'header');			
        $tbl1->addCell('Jml mhs', null, 'header');
        $tbl1->addCell('Jml T', null, 'header');	   
       	$tbl1->addCell('Aksi', null, 'header');	
		
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
            $txt = $row['jmlT'] != $row['jml_mhs'] ? '<font color="red">'.$row['jmlT'].'</font>' : $row['jmlT'];
		      $tbl1->addCell($txt, null, 'data'); 		  
		 	$link1='javascript:inputnilai("'.$row['nokmkkrs'].'","'.$row['shiftkrs'].'","'.$row['kelaskrs'].'","'.$kd_fak.'")';
			$tbl1->addCell("<a href='".$link1."'>Input</a>", null, 'data');
		}
		     
	  }	   	 
	   
	  $txt="<br>".$awl_form.$tbl1->display("")."</form>";
         
	  
	   $html_txt="<fieldset>";
	   $html_txt.="<legend>Prodi : $vnm_prodi </legend><div>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}
	
	function list_sbrnmtk($kd_fak,$kd_prodi,$ta)
	{	
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);

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
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);

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
		  
          $data1=$dt_jml_sks->getMHS("NO_KTP='".$row['NO_KTP']."' and  thsmskrs='".$ta."' and flag_krs=1");
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
		     $link1='javascript:inputkrs("'.$row['NO_KTP'].'")';
			 $tbl1->addCell("<a href='".$link1."'>Input</a>", null, 'data');
		  }else{
		     $link='javascript:deletekrs("'.$kd_fak.'","'.$row['NO_KTP'].'")';
			 $link1='javascript:inputkrs("'.$row['NO_KTP'].'")';
			  
			 $tbl1->addCell("<a href='".$link1."'>Edit</a>"." "."<a href='".$link."'>Delete</a>", null, 'data');
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

	function list_khs($kd_fak,$kd_prodi,$thn_msk,$ta)
	{	
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);
		
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_khs","width"=>"100%"));
		
		$tbl1->addRow();
        $tbl1->addCell('KTP', null, 'header',array("align" => "center","valign"=>"middle"));	    
		$tbl1->addCell('Nama', null, 'header',array("align" => "center","valign"=>"middle"));
		$tbl1->addCell('NPM', null, 'header',array("align" => "center","valign"=>"middle"));	   
		$tbl1->addCell('R/N', null, 'header',array("align" => "center","valign"=>"middle"));
        
		  
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
		  
		  
          $data1=$dt_jml_sks->getMHS("NO_KTP='".$row['NO_KTP']."' and  thsmskrs='".$ta."' and flag_krs=1");
		  $jmlsks=0;
		  if(!empty($data1))
          {
		    foreach($data1 as $row1)
		    {
			  $jmlsks=$row1['jml_sks'];
			}
		  }
		  $tbl1->addCell($jmlsks, null, 'data');
          
		  if($jmlsks>0){
		     $link1='javascript:cetak_khs("'.$kd_fak.'","'.$kd_prodi.'","'.$ta.'","'.$row['NO_KTP'].'")';
			 $tbl1->addCell("<a href='".$link1."'>Cetak</a>", null, 'data');		  
		  }else{
             $tbl1->addCell("Cetak", null, 'data');
		   }
		    		  
		 	  	  
		}
		     
	  }	   	 
	   
	  $txt="<br>".$tbl1->display("");
         
	  
	   $html_txt="<fieldset>";
	   $html_txt.="<legend>Prodi : $vnm_prodi Angkatan : $thn_msk </legend><div>";
	   $html_txt.=$txt;
	   $html_txt.="</fieldset>";
	  
	  return $html_txt;
	}
	
	function Data_to_pdf($fak,$prodi,$thn,$id_opt)
	{
        
		
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);
		
		
		$sql="kd_fakultas='".$fak."' and kd_prodi='".$prodi."' and Tahun_masuk=".$thn;				
		$data = $this->dt_mhs->getOrderedData($sql); 
		
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","align"=>"right"));
		 $tbl1->addRow();
		 $tbl1->addCell("Baleendah, .... - .......... - ......", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("Operator PUMHS", null, 'data',array("align"=>"center"));
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("( ................... )", null, 'data',array("align"=>"center")); 
         $txt2 = $tbl1->display("");
		
		
		if(!empty($data))
      {	 
		$i=0;
		$page=1;
		$tabel="";
		$tgl=date("Y-m-d H:i:s");
		foreach($data as $row)
		{
		  
		   if ($page==1){
		   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs1","width"=>"100%","border"=>"1"));
		
		   $tbl->addRow();
           $tbl->addCell('No.', null, 'header');	    
		   $tbl->addCell('Nama', null, 'header');
		   $tbl->addCell('L/P', null, 'header');
           $tbl->addCell('NPM', null, 'header');		
		   $tbl->addCell('Validasi', null, 'header');
             
		    $page=0;
		   }		  
		  
		   $i=$i+1;
		   $tbl->addRow();        
		   $tbl->addCell($this->ismrhitl($row['optcid'],$i), null, 'data');
		  	
           $tbl->addCell($this->ismrhitl($row['optcid'],strtoupper($row['Nama_mahasiswa'])), null, 'data');
		   $tbl->addCell($this->ismrhitl($row['optcid'],$row['Jenis_kelamin']), null, 'data');
		   $tbl->addCell($this->ismrhitl($row['optcid'],strtoupper($row['NIM'])), null, 'data');
		   $txt=$this->validasi($row);
		   $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		  
          if(($i % 15)==0){		  
            
			
			$txt='<center><H2>PENDATAAN ULANG MAHASISWA (PUMHS)</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Kondisi Data Pada Tanggal :'.$tgl.'</center><br>';
			$tabel.='<div id="header">Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt2.'<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div></span>';
            $page=1;			
		  }
		}
      }	
        $txt='<center><H2>PENDATAAN ULANG MAHASISWA (PUMHS)</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Kondisi Data Pada Tanggal :'.$tgl.'</center><br>';
	    $tabel.='<div id="header">Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt2.'<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div></span>';
		
		            
		
		
		$txt='<html><head>';
		//$txt.='<script type="text/php">';
		//$txt.='if (isset($pdf)) {';
		//$txt.='    $font=Font_Metrics::get_font("helvetica","bold");';
		//$txt.='    $pdf->page_text(72,18,"Header : {PAGE_NUM} of {PAGE_COUNT}",$font,6,array(0,0,0));';	
		//$txt.='}';
		//$txt.='</script>'
		$txt.='<style>#header{ position: fixed; left: 0px; top: -15px; right: 0px; height: 20px; border-bottom: 2px solid gray;} #footer { position: fixed;  bottom: 0px;  left: 0px;  right: 0px;  height: 50px;  border-top: 2px solid gray;} .pagenum:before {  content: counter(page);} .page { page-break-after:always; } </style>';
		$txt.='</head><body>';		
		$txt.=$tabel;
		$txt.='</body></html>';
		
      	
		  $base_path = dirname(dirname(__FILE__)). '/cetak/';	 
		  	  
		  $tmp = "Data PUMHS - ".$prodi.$thn." ".date("dmY His").".pdf";
		  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($txt);
          $dompdf->set_paper('a4', 'portrait');
		  $dompdf->render();
		  $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);
		  
		  $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		  $dt_opt_ctk_log->insert($tmp,$id_opt); 

          if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak/") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }    		  
		  
		return $base_path.$tmp;
	  
	}
	
	
	function Data_blmlyk_Verifikasi_to_pdf($fak,$prodi,$thn,$id_opt)
	{
        
		
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);
		
		
		$sql="kd_fakultas='".$fak."' and kd_prodi='".$prodi."' and Tahun_masuk=".$thn." and validasi=0";				
		$data = $this->dt_mhs->getOrderedData($sql); 
		
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","align"=>"right"));
		 $tbl1->addRow();
		 $tbl1->addCell("Baleendah, .... - .......... - ......", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("Operator PUMHS", null, 'data',array("align"=>"center"));
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("( ................... )", null, 'data',array("align"=>"center")); 
         $txt2 = $tbl1->display("");
		
		$i=0;
		$tgl=date("Y-m-d H:i:s");
		if(!empty($data))
      {	 
		
		$page=1;
		$tabel="";		
		foreach($data as $row)
		{
		  
		   if ($page==1){
		   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs1","width"=>"100%","border"=>"1"));
		
		   $tbl->addRow();
           $tbl->addCell('No.', null, 'header');	    
		   $tbl->addCell('Nama', null, 'header');
		   $tbl->addCell('L/P', null, 'header');
           $tbl->addCell('NPM', null, 'header');		
		   $tbl->addCell('Validasi', null, 'header');
             
		    $page=0;
		   }		  
		  
		   $i=$i+1;
		   $tbl->addRow();        
		   $tbl->addCell($i, null, 'data');
		  	
           $tbl->addCell(strtoupper($row['Nama_mahasiswa']), null, 'data');
		   $tbl->addCell($row['Jenis_kelamin'], null, 'data');
		   $tbl->addCell(strtoupper($row['NIM']), null, 'data');
		   $txt=$this->validasi($row);
		   $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		  
          if(($i % 15)==0){		  
            
			
			$txt='<center><H2>DATA MAHASISWA BELUM LAYAK VERIFIKASI</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Tanggal Cetak :'.$tgl.'</center><br>';
			$tabel.='<div id="header">Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt2.'<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div></span>';
            $page=1;			
		  }
		}
      
		  if(($i % 15)!=0){ 
			$txt='<center><H2>DATA MAHASISWA BELUM LAYAK VERIFIKASI</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Tanggal Cetak :'.$tgl.'</center><br>';
			$tabel.='<div id="header">Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt2.'<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div></span>';
		  }
	  }	
       
		            
		if($i>0){ 
		
		$txt='<html><head>';
		//$txt.='<script type="text/php">';
		//$txt.='if (isset($pdf)) {';
		//$txt.='    $font=Font_Metrics::get_font("helvetica","bold");';
		//$txt.='    $pdf->page_text(72,18,"Header : {PAGE_NUM} of {PAGE_COUNT}",$font,6,array(0,0,0));';	
		//$txt.='}';
		//$txt.='</script>'
		$txt.='<style>#header{ position: fixed; left: 0px; top: -15px; right: 0px; height: 20px; border-bottom: 2px solid gray;} #footer { position: fixed;  bottom: 0px;  left: 0px;  right: 0px;  height: 50px;  border-top: 2px solid gray;} .pagenum:before {  content: counter(page);} .page { page-break-after:always; } </style>';
		$txt.='</head><body>';		
		$txt.=$tabel;
		$txt.='</body></html>';
		
		}
		
      	$base_path = dirname(dirname(__FILE__)). '/cetak/';
			  
		$tmp = "Data Blm Lyk Verifikasi PUMHS - ".$prodi.$thn." ".date("dmY His").".pdf";
		if($i>0){  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($txt);
          $dompdf->set_paper('a4', 'portrait');
		  $dompdf->render();
		  $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);
		  
		  $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		  $dt_opt_ctk_log->insert($tmp,$id_opt); 

          if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak/") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }    		  
		  
		return $base_path.$tmp;
	  }else
		 {
		   return 0;
		 
		 }
	}
	
	
	function Data_hsl_Verifikasi_to_pdf($fak,$prodi,$thn,$id_opt)
	{
        
		
		            $dt_prodi=new dt_prodi;
					$vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);
		
		
		$sql="kd_fakultas='".$fak."' and kd_prodi='".$prodi."' and Tahun_masuk=".$thn." and verifikasi=1";				
		$data = $this->dt_mhs->getOrderedData($sql); 
		
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","align"=>"right"));
		 $tbl1->addRow();
		 $tbl1->addCell("Baleendah, .... - .......... - ......", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("Operator PUMHS", null, 'data',array("align"=>"center"));
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("( ................... )", null, 'data',array("align"=>"center")); 
         $txt2 = $tbl1->display("");
		
		$i=0;
		$tgl=date("Y-m-d H:i:s");
		if(!empty($data))
      {	 
		
		$page=1;
		$tabel="";		
		foreach($data as $row)
		{
		  
		   if ($page==1){
		   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs1","width"=>"100%","border"=>"1"));
		
		   $tbl->addRow();
           $tbl->addCell('No.', null, 'header');	    
		   $tbl->addCell('Nama', null, 'header');
		   $tbl->addCell('L/P', null, 'header');
           $tbl->addCell('NPM', null, 'header');		
		   //$tbl->addCell('Validasi', null, 'header');
             
		    $page=0;
		   }		  
		  
		   $i=$i+1;
		   $tbl->addRow();        
		   $tbl->addCell($i, null, 'data');
		  	
           $tbl->addCell(strtoupper($row['Nama_mahasiswa']), null, 'data');
		   $tbl->addCell($row['Jenis_kelamin'], null, 'data');
		   $tbl->addCell(strtoupper($row['NIM']), null, 'data');
		   //$txt=$this->validasi($row);
		   //$tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		  
          if(($i % 15)==0){		  
            
			
			$txt='<center><H2>DATA MAHASISWA TERVERIFIKASI</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Tanggal Cetak :'.$tgl.'</center><br>';
			$tabel.='<div id="header">Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt2.'<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div></span>';
            $page=1;			
		  }
		}
      
		  if(($i % 15)!=0){ 
			$txt='<center><H2>DATA MAHASISWA TERVERIFIKASI</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Tanggal Cetak :'.$tgl.'</center><br>';
			$tabel.='<div id="header">Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt2.'<div id="footer"><table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table></div></span>';
		  }
	  }	
       
		            
		if($i>0){ 
		
		$txt='<html><head>';
		//$txt.='<script type="text/php">';
		//$txt.='if (isset($pdf)) {';
		//$txt.='    $font=Font_Metrics::get_font("helvetica","bold");';
		//$txt.='    $pdf->page_text(72,18,"Header : {PAGE_NUM} of {PAGE_COUNT}",$font,6,array(0,0,0));';	
		//$txt.='}';
		//$txt.='</script>'
		$txt.='<style>#header{ position: fixed; left: 0px; top: -15px; right: 0px; height: 20px; border-bottom: 2px solid gray;} #footer { position: fixed;  bottom: 0px;  left: 0px;  right: 0px;  height: 50px;  border-top: 2px solid gray;} .pagenum:before {  content: counter(page);} .page { page-break-after:always; } </style>';
		$txt.='</head><body>';		
		$txt.=$tabel;
		$txt.='</body></html>';
		
		}
		
      	$base_path = dirname(dirname(__FILE__)). '/cetak/';
		  
		  
		  
		  $tmp = "Data Hasil Verifikasi PUMHS - ".$prodi.$thn." ".date("dmY His").".pdf";
		if($i>0){  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($txt);
          $dompdf->set_paper('a4', 'portrait');
		  $dompdf->render();
		  $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);
		  
		  $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		  $dt_opt_ctk_log->insert($tmp,$id_opt); 

          if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak/") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }    		  
		  
		return $base_path.$tmp;
	  }else
		 {
		   return 0;
		 
		 }
	}
	
	
	private function ismrhitl($id_opt,$data)
	{
	   if($id_opt<>''){
	      return "<i><u>".$data."</u></i>";
	   }else{
	      return "$data";
	   }
	}
	
	
	function Data_verifikasi_to_pdf($fak,$prodi,$thn,$id_opt)
	{
	    
		
		           $dt_prodi=new dt_prodi;
				   $vnm_prodi=$dt_prodi->getnmprodi($kd_fak,$kd_prodi);
		
		
		$sql="kd_fakultas='".$fak."' and kd_prodi='".$prodi."' and Tahun_masuk=".$thn." and (verifikasi=0 or verifikasi=1) and validasi=1 and (nm_file = '' OR nm_file IS NULL)";				
		
		$data = $this->dt_mhs->getOrderedData($sql); 
		
		
		$tmp_txt="<div>Pernyataan :<br>Saya yang bertanda tangan di bawah ini menyatakan, bahwa data tersebut diatas benar adanya dan saya bertanggung jawab bilamana dikemudian hari terdapat kekeliruan.</div>";
		
		$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","align"=>"right"));
		 $tbl1->addRow();
		 $tbl1->addCell("Baleendah, .... - .......... - ......", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("Ketua Prodi. ".$vnm_prodi, null, 'data',array("align"=>"center"));
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		  $tbl1->addCell("<br>", null, 'data');
		 $tbl1->addRow();
		 $tbl1->addCell("( ................... )", null, 'data',array("align"=>"center")); 
         $txt2 = $tmp_txt.'<br>'.$tbl1->display("");
		
		$tmp_txt="<div>Pernyataan :<br>Saya yang bertanda tangan di bawah ini menyatakan, bahwa data tersebut diatas benar adanya dan saya bertanggung jawab bilamana dikemudian hari terdapat kekeliruan.</div>";
		
		
		 $txt_no_form =$prodi.$thn.date("dmY His");
		
		$nm_file ="Form Verifikasi - ".$prodi.$thn." ".date("dmY His");
		
		$i=0;
		if(!empty($data))
      {	 
		
		$page=1;
		$jml_pg=1;
		$tabel="";
		$tgl=date("Y-m-d H:i:s");
		$ctk_ket=0;
		foreach($data as $row)
		{
		  
		   if ($page==1){
		   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs1","width"=>"100%","border"=>"1"));
		
		   $tbl->addRow();
           $tbl->addCell('No.', null, 'header');	    
		   $tbl->addCell('Nama', null, 'header');
		   $tbl->addCell('L/P', null, 'header');
           $tbl->addCell('NPM', null, 'header');		
		   $tbl->addCell('Alamat', null, 'header');
		   $tbl->addCell('Terverifikasi', null, 'header');
		   $tbl->addCell('Tidak Terverfikasi', null, 'header');
             
		    $page=0;
		   }		  

		    		   
		   $i=$i+1;
		   $tbl->addRow();        
		   $tbl->addCell($this->ismrhitl($row['optcid'],$i), null, 'data');
		  	
           $tbl->addCell($this->ismrhitl($row['optcid'],strtoupper($row['Nama_mahasiswa'])), null, 'data');
		   $tbl->addCell('<center>'.$this->ismrhitl($row['optcid'],$row['Jenis_kelamin']).'</center>', null, 'data');
		   $tbl->addCell('<center>'.$this->ismrhitl($row['optcid'],strtoupper($row['NIM'])).'</center>', null, 'data');
		   $tbl->addCell("<FONT SIZE='1'>".$this->ismrhitl($row['optcid'],$row['Alamat'])."</FONT>", null, 'data');
		   $chkbxk ='<center><img src="../image/checkbox.png" /></center>';
		   //$chkbxk ="";
		   $tbl->addCell($chkbxk, null, 'data');
           $tbl->addCell($chkbxk, null, 'data');
		   
		   if($row['optcid']!="")
		   {
		     $ctk_ket=1;
		   }

           $this->dt_mhs->update_nm_file($row['NO_KTP'],$nm_file,$tgl,$id_opt);
		   
          
		   
          if(($i % 12)==0){   
			
			$txt='<br>No Formulir : '.$txt_no_form.$jml_pg.'<br><center><H2>FORMULIR VERIFIKASI</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Kondisi Data Pada Tanggal :'.$tgl.'</center><br>';
			$tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","width"=>"100%","border"=>"1"));
			 $tbl1->addRow();
			 $tbl1->addCell("No. Formulir : ".$txt_no_form.$jml_pg."<br><center>Serah Terima<br>Operator Ke Prodi</center>", null, 'data',array("colspan"=>"2"));
			 $tbl1->addCell("No. Formulir : ".$txt_no_form.$jml_pg."<center>Serah Terima<br>Prodi Ke Operator</center>", null, 'data',array("colspan"=>"2"));
			 $tbl1->addRow();
			 $tbl1->addCell("<center>Operator<br><br><br><br><br>( ................... )</center>", null, 'data');
			 $tbl1->addCell("<center>Ketua Prodi.<br><br><br><br><br>( ................... )</center>", null, 'data');
			 $tbl1->addCell("<center>Ketua Prodi.<br><br><br><br><br>( ................... )</center>", null, 'data');
			 $tbl1->addCell("<center>Operator<br><br><br><br><br>( ................... )</center>", null, 'data');
			  
			 $txt_footer = $tbl1->display("");
			 //$txt_footer = "";
		   	
		    $txt_ket="";
			
			if($ctk_ket==1){
			 $txt_ket="Keterangan : Yang digaris bawahi dan di cetak miring di input oleh operator fakultas.<br>";
			 $ctk_ket=0; 
			}
			
			$tabel.='<div id="header"><table width="100%"><tr><td>Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</td> <td><span class="pagenum"></span></td></tr></table></div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt_ket.$txt2.'<div id="footer">'.$txt_footer.'</div></span>';
            
			$page=1;
            $jml_pg=$jml_pg+1;			
		  }
		  
		}
      }	
        
	   if(($i % 12)!=0){	
		$txt='<br>No Formulir : '.$txt_no_form.$jml_pg.'<br><center><H2>FORMULIR VERIFIKASI</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Kondisi Data Pada Tanggal :'.$tgl.'</center><br>';
	    $tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","width"=>"100%","border"=>"1"));
			 $tbl1->addRow();
			 $tbl1->addCell("No. Formulir : ".$txt_no_form.$jml_pg."<br><center>Serah Terima<br>Operator Ke Prodi</center>", null, 'data',array("colspan"=>"2"));
			 $tbl1->addCell("No. Formulir : ".$txt_no_form.$jml_pg."<center>Serah Terima<br>Prodi Ke Operator</center>", null, 'data',array("colspan"=>"2"));
			 $tbl1->addRow();
			 $tbl1->addCell("<center>Operator<br><br><br><br><br>( ................... )</center>", null, 'data');
			 $tbl1->addCell("<center>Ketua Prodi.<br><br><br><br><br>( ................... )</center>", null, 'data');
			 $tbl1->addCell("<center>Ketua Prodi.<br><br><br><br><br>( ................... )</center>", null, 'data');
			 $tbl1->addCell("<center>Operator<br><br><br><br><br>( ................... )</center>", null, 'data');
			  
			 $txt_footer = $tbl1->display("");
			 //$txt_footer = "";
		    
			$txt_ket="";
			
			if($ctk_ket==1){
			 $txt_ket="Keterangan : Yang digaris bawahi dan di cetak miring di input oleh operator fakultas.<br>";
			   $ctk_ket=0;
			}
			
			$tabel.='<div id="header"><table width="100%"><tr><td>Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</td> <td><span class="pagenum"></span></td></tr></table></div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt_ket.$txt2.'<div id="footer">'.$txt_footer.'</div></span>';
		    
			//$tabel.='<div id="header"><table width="100%"><tr><td>Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</td> <td><span class="pagenum"></span></td></tr></table></div><span class="page">'.$txt.'<br>'.$txt2.'<div id="footer">'.$txt_footer.'</div></span>';
		
		}
		            
		if($i>0){
		
		$txt='<html><head>';
		//$txt.='<script type="text/php">';
		//$txt.='if (isset($pdf)) {';
		//$txt.='    $font=Font_Metrics::get_font("helvetica","bold");';
		//$txt.='    $pdf->page_text(72,18,"Header : {PAGE_NUM} of {PAGE_COUNT}",$font,6,array(0,0,0));';	
		//$txt.='}';
		//$txt.='</script>'
		$txt.='<style>#header{ position: fixed; left: 0px; top: -15px; right: 0px; height: 20px; border-bottom: 2px solid gray;} #footer { position: fixed;  bottom: 0px;  left: 0px;  right: 0px;  height: 250px; } .pagenum:before {  content: counter(page);} .page { page-break-after:always; } </style>';
		$txt.='</head><body>';		
		$txt.=$tabel;
		$txt.='</body></html>';

		}
		
      		  
		  
		  
		 $base_path = dirname(dirname(__FILE__)). '/cetak/';
		  
		$tmp ="";  
		if($i>0){   
		  $tmp = $nm_file.".pdf";
		  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($txt);
          $dompdf->set_paper('legal', 'portrait');
		  $dompdf->render();
		  $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);
		  
		  $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		  $dt_opt_ctk_log->insert($tmp,$id_opt); 
        
          if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak/") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }    		  
		  
		 return $base_path.$tmp;
		 }else
		 {
		   return 0;
		 
		 }
	
	}
	
	function persiapan_kuliah($kd_fak)
	{
	        $txt='<div id="tabs3">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Perwalian</a></li>';
			$txt.='<li><a href="#tabs-2">Kartu Rencana Studi</a></li>';
			$txt.='<li><a href="#tabs-3">Sebaran Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-4">Input Nilai</a></li>';
			$txt.='<li><a href="#tabs-5">Kartu Hasil Studi</a></li>';
			$txt.='<li><a href="#tabs-6">Kurikulum</a></li>';
			$txt.='</ul>';
			
			$txt.='<div id="tabs-1">';						
			$txt.=$this->tab_perwalian($kd_fak);
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			$txt.=$this->tab_krs($kd_fak);
			$txt.='</div>';
            $txt.='<div id="tabs-3">';
			$txt.=$this->tab_sbrnmtk($kd_fak);
			$txt.='</div>';
			$txt.='<div id="tabs-4">';
			$txt.=$this->tab_nilai($kd_fak);
			$txt.='</div>';	
			$txt.='<div id="tabs-5">';
			$txt.=$this->tab_khs($kd_fak);
			$txt.='</div>';
			$txt.='<div id="tabs-6">';
			$txt.=$this->tab_kur($kd_fak);
			$txt.='</div>';
			$txt.='</div>';
	   
	   
	   return  $txt;
	}

	function tab_kur($kd_fak)
	{
	 $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
	        $txt_sem='<select name="sem_kur" id="sem_kur">'.$txt3.'</select>';
			$txt_prodi='<select name="Prodi_kur" id="Prodi_kur">'.$txt1.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." ".$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_kur('".$kd_fak."')"));
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_kur'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,0,11,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	}

	function tab_nilai($kd_fak)
	{
	 $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
	        $txt_sem='<select name="sem_nilai" id="sem_nilai">'.$txt3.'</select>';
			$txt_prodi='<select name="Prodi_nilai" id="Prodi_nilai">'.$txt1.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." ".$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_nilai('".$kd_fak."')"));
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_nilai'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,0,9,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	}
	
	function tab_sbrnmtk($kd_fak)
	{
	 $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." ".$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_sbrnmtk('".$kd_fak."')"))."<button onclick='cetak_DHMD(".$tmp.")'>Cetak DHMD</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_sbrnmtk'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,0,8,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	}
	
	function tab_khs($kd_fak)
	{
	 $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
	        $txt_sem='<select name="sem_khs" id="sem_khs">'.$txt3.'</select>';
			$txt_prodi='<select name="Prodi_khs" id="Prodi_khs">'.$txt1.'</select>';
	        $txt_angkatan='<select name="thn_khs" id="thn_khs">'.$txt2.'</select>';
	        $frm = new HTML_Form();
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_khs('".$kd_fak."')"));//"<button onclick='cetak_jml_sks(".$tmp.")'>Cetak Jumlah SKS</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_khs'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,10,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	}
	
	function tab_krs($kd_fak)
	{
	 $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,7,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	}
	
	function tab_perwalian($kd_fak)
	{
	            $txt1="";
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$kd_fak."'");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['prodi']."</option>";
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
	        $txt.= "Semester ".$txt_sem." Prodi ".$txt_prodi." Angkatan ".$txt_angkatan.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_perwalian('".$kd_fak."')"))."<button onclick='cetak_perwalian(".$tmp.")'>Cetak Absensi Perwalian</button>";
	        $txt.="</fieldset>";
			$txt.="<div id = 'data_absperwalian'>";
			$txt.=$this->hsl_filter($kd_fak,$vkd_prodi,$thn_msk,6,"",$ta);
			$txt.="</div>";
	  return $txt;
	
	
	}
	
	
	function Data_absperwalian_to_pdf($fak,$prodi,$thn,$id_opt)
	{
	    
		
		            $dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_fakultas='".$fak."' and kd_prodi='".$prodi."'");
					$vnm_prodi="";
					foreach ($data as $r){						
						  $vnm_prodi=$r['prodi'];						
					}
		
		
		$sql="kd_fakultas='".$fak."' and kd_prodi='".$prodi."' and Tahun_masuk=".$thn." and verifikasi=1";				
		
		$data = $this->dt_mhs->getOrderedData($sql); 
		
		
		     $tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","width"=>"40%","align"=>"right","border"=>"1"));
			 $tbl1->addRow();
			 $tbl1->addCell("<center>Baleendah, .... - .......... - ......</center>", null, 'data',array("colspan"=>"2"));
			 $tbl1->addRow();
			 $tbl1->addCell("<center>Mengetahui</center>", null, 'data');
			 $tbl1->addCell("<center>Menyetujui</center>", null, 'data');
			 $tbl1->addRow();
			 $tbl1->addCell("<center>Ketua Prodi.<br><br><br><br><br>( ................... )</center>", null, 'data');
			 $tbl1->addCell("<center>Dosen Wali<br><br><br><br><br>( ................... )</center>", null, 'data');
		
         $txt2=$tbl1->display("");		
		
		 $txt_no_form =$prodi.$thn.date("dmY His");
		
		$nm_file ="Absen Perwalian - ".$prodi.$thn." ".date("dmY His");
		
		$i=0;
		if(!empty($data))
      {	 
		
		$page=1;
		$jml_pg=1;
		$tabel="";
		$tgl=date("Y-m-d H:i:s");
		$ctk_ket=0;
		foreach($data as $row)
		{
		  
		   if ($page==1){
		   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs1","width"=>"100%","border"=>"1"));
		
		   $tbl->addRow();
           $tbl->addCell('No.', null, 'header',array("align" => "center","valign"=>"middle","rowspan"=>"2"));	    
		   $tbl->addCell('Nama', null, 'header',array("align" => "center","valign"=>"middle","rowspan"=>"2"));
		   $tbl->addCell('NPM', null, 'header',array("align" => "center","valign"=>"middle","rowspan"=>"2"));	   
		   $tbl->addCell('TTD', null, 'header',array("align" => "center","valign"=>"middle","rowspan"=>"2"));	   
		   $tbl->addCell('Status', null, 'header',array("align" => "center","valign"=>"middle","colspan"=>"4"));
	       $tbl->addRow(); 		   	    
       	   $tbl->addCell('Lulus', null, 'header');
		   $tbl->addCell('Cuti', null, 'header');
		   $tbl->addCell('Keluar', null, 'header');
		   $tbl->addCell('Non Aktif', null, 'header');
             
		    $page=0;
		   }		  

		    		   
		   $i=$i+1;
		   $tbl->addRow();        
		   $tbl->addCell($this->ismrhitl($row['optcid'],$i), null, 'data');
		  	
           $tbl->addCell($this->ismrhitl($row['optcid'],strtoupper($row['Nama_mahasiswa'])), null, 'data');
		   $tbl->addCell('<center>'.$this->ismrhitl($row['optcid'],strtoupper($row['NIM'])).'</center>', null, 'data');
		   $chkbxk ='<center><img src="../image/checkbox.png" /></center>';
		   //$chkbxk ="";
		   $tbl->addCell("<center>.........</center>", null, 'data');
           $tbl->addCell($chkbxk, null, 'data');
		   $tbl->addCell($chkbxk, null, 'data');
           $tbl->addCell($chkbxk, null, 'data');
		   $tbl->addCell($chkbxk, null, 'data');
		   
		   if($row['optcid']!="")
		   {
		     $ctk_ket=1;
		   }

           
		   
          
		   
          if(($i % 12)==0){   
			
			$txt='<br>No Formulir : '.$txt_no_form.$jml_pg.'<br><center><H2>ABSEN PERWALIAN</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Kondisi Data Pada Tanggal :'.$tgl.'</center><br>';
			
			 $txt_footer = '<table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table>';
		   	
		    $txt_ket="Keterangan :<br><ul>";
			$txt_ket.="<li>Mahasiswa yang mebubuhkan tanda tangan dinyatakan sebagai mahasiswa aktif.</li>";
			$txt_ket.="<li>Status yang lain ditetapkan oleh prodi. berdasarkan ketersediaan dokumen.</li>";
			$txt_ket.="<li>Mohon lampirkan bersama absensi ini dokumen pendukung untuk status Cuti,Non Aktif,Keluar.</li>";
			if($ctk_ket==1){
			 $txt_ket.="<li>Yang digaris bawahi dan di cetak miring di input oleh operator fakultas.</li>";
			 $ctk_ket=0; 
			}
			$txt_ket.="</ul>";
			
			$tabel.='<div id="header"><table width="100%"><tr><td>Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</td> <td><span class="pagenum"></span></td></tr></table></div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt_ket.$txt2.'<div id="footer">'.$txt_footer.'</div></span>';
            
			$page=1;
            $jml_pg=$jml_pg+1;			
		  }
		  
		}
      }	
        
	   if(($i % 12)!=0){	
		$txt='<br>No Formulir : '.$txt_no_form.$jml_pg.'<br><center><H2>ABSEN PERWALIAN</H2>Program Studi '.$vnm_prodi.'<br>Angkatan : '.$thn.'<br>Kondisi Data Pada Tanggal :'.$tgl.'</center><br>';
	    $tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_ttd","width"=>"100%","border"=>"1"));
			$txt_footer = '<table width="100%"><tr><td>Tim Pengembangan Sistem Informasi (PSI)</td> <td><span class="pagenum"></span></td></tr></table>';
		    
			$txt_ket="Keterangan :<br><ul>";
			$txt_ket.="<li>Mahasiswa yang mebubuhkan tanda tangan dinyatakan sebagai mahasiswa aktif.</li>";
			$txt_ket.="<li>Status yang lain ditetapkan oleh prodi. berdasarkan ketersediaan dokumen.</li>";
			$txt_ket.="<li>Mohon lampirkan bersama absensi ini dokumen pendukung untuk status Cuti,Non Aktif,Keluar.</li>";
			
			
			if($ctk_ket==1){
			 $txt_ket.="<li>Yang digaris bawahi dan di cetak miring di input oleh operator fakultas.</li>";
			   $ctk_ket=0;
			}
			
			$txt_ket.="</ul>";
			
			$tabel.='<div id="header"><table width="100%"><tr><td>Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</td> <td><span class="pagenum"></span></td></tr></table></div><span class="page">'.$txt.$tbl->display("").'<br>'.$txt_ket.$txt2.'<div id="footer">'.$txt_footer.'</div></span>';
		    
			//$tabel.='<div id="header"><table width="100%"><tr><td>Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS)</td> <td><span class="pagenum"></span></td></tr></table></div><span class="page">'.$txt.'<br>'.$txt2.'<div id="footer">'.$txt_footer.'</div></span>';
		
		}
		            
		if($i>0){
		
		$txt='<html><head>';
		//$txt.='<script type="text/php">';
		//$txt.='if (isset($pdf)) {';
		//$txt.='    $font=Font_Metrics::get_font("helvetica","bold");';
		//$txt.='    $pdf->page_text(72,18,"Header : {PAGE_NUM} of {PAGE_COUNT}",$font,6,array(0,0,0));';	
		//$txt.='}';
		//$txt.='</script>'
		$txt.='<style>#header{ position: fixed; left: 0px; top: -15px; right: 0px; height: 20px; border-bottom: 2px solid gray;} #footer { position: fixed;  bottom: 0px;  left: 0px;  right: 0px;  height: 50px;  border-top: 2px solid gray; } .pagenum:before {  content: counter(page);} .page { page-break-after:always; } </style>';
		$txt.='</head><body>';		
		$txt.=$tabel;
		$txt.='</body></html>';

		}
		
      	$base_path = dirname(dirname(__FILE__)). '/cetak/';
		  
		$tmp ="";  
		if($i>0){   
		  $tmp = $nm_file.".pdf";
		  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($txt);
          $dompdf->set_paper('legal', 'portrait');
		  $dompdf->render();
		  $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);
		  
		  $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		  $dt_opt_ctk_log->insert($tmp,$id_opt); 
        
          if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }    		  
		  
		 return $base_path.$tmp;
		 }else
		 {
		   return 0;
		 
		 }
	
	}
	
	function DHMD_FKIP($fak,$prodi,$thn,$id_opt,$data)
	{
	      $nm_shift=array('R'=>'Reguler','N'=>'Non Reguler');
          $objPHPExcel = new PHPExcel();
		  $Sheet = $objPHPExcel->getActiveSheet();
	   
	      
		  //$jml_mtk=$dt_krs->numrows; 
		  
		  $j=0;
		  $first_row=1;
		  foreach($data as $row)
		  {
					   if($j>0)
					   {
					    $Sheet = $objPHPExcel->createSheet($j);						 						 
					   }
					  					  
					  
					   $Sheet->getColumnDimension('A')->setWidth(3.29);
					   $Sheet->getColumnDimension('B')->setWidth(22.29);
					   $Sheet->getColumnDimension('C')->setWidth(1.50);
					   $Sheet->getColumnDimension('D')->setWidth(10.00);
					   $Sheet->getColumnDimension('E')->setWidth(7.00);

					   $Sheet->getColumnDimension('F')->setWidth(7.00);
					   $Sheet->getColumnDimension('G')->setWidth(7.00);
					   $Sheet->getColumnDimension('H')->setWidth(7.00);
					   $Sheet->getColumnDimension('I')->setWidth(7.00);

					   $Sheet->getColumnDimension('J')->setWidth(7.00);
					   $Sheet->getColumnDimension('K')->setWidth(7.00);
					   $Sheet->getColumnDimension('L')->setWidth(7.00);
					   $Sheet->getColumnDimension('M')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('N')->setWidth(7.00);
					   $Sheet->getColumnDimension('O')->setWidth(7.00);
					   $Sheet->getColumnDimension('P')->setWidth(7.00);
					   $Sheet->getColumnDimension('Q')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('R')->setWidth(7.00);
					   $Sheet->getColumnDimension('S')->setWidth(8.00);
					   
					  
									$dt_prodi=new dt_prodi;
									$data = $dt_prodi->getData("kd_fakultas='".$fak."' and kd_prodi='".$prodi."'");
									$vnm_prodi="";
									foreach ($data as $r){						
										  $vnm_prodi=$r['prodi'];						
									}
						
									$dt_fak=new dt_fak;
									$data = $dt_fak->getData("kd_fakultas='".$fak."'");
									$vnm_fak="";
									foreach ($data as $r){						
										  $vnm_fak=$r['fakultas'];						
									}
						  
						
						 
						
									  $Sheet->setCellValue('A'.$first_row, 'PROGRAM STUDI '.strtoupper($vnm_prodi));
									  $Sheet->setCellValue('A'.($first_row+1), strtoupper($vnm_fak));
									  $Sheet->setCellValue('A'.($first_row+2), 'UNIVERSITAS BALE BANDUNG');
									  $Sheet->getStyle('A'.$first_row.':A'.($first_row+2))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														)
													)
											);
									  
									  $Sheet->setCellValue('A'.($first_row+5), 'DAFTAR HADIR MAHASISWA DAN DOSEN (DHMD)');
									  $Sheet->mergeCells('A'.($first_row+5).':S'.($first_row+5));
									  $Sheet->getStyle('A'.($first_row+5).':S'.($first_row+5))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+5).':S'.($first_row+5))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
									  
									  $Sheet->getStyle('A'.($first_row+5).':S'.($first_row+5))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 12
														)
													)
											);		
									  
									  $Sheet->setCellValue('A'.($first_row+7), 'Mata Kuliah');
									  $Sheet->setCellValue('A'.($first_row+8), 'Dosen');
									  $Sheet->setCellValue('A'.($first_row+9), 'Asisten'); 
									  $Sheet->setCellValue('A'.($first_row+10), 'Semester / Tahun Akademik');
									  $Sheet->setCellValue('A'.($first_row+11), 'Kelas');
									  
									   
									   //$thnsms = $vbaca_krs->TA();
									   $tmp = str_split($thn, 4);	  
									   $thnsms=$tmp[0];
									  
									  $Sheet->setCellValue('C'.($first_row+7),  ': ');
									  $Sheet->setCellValue('C'.($first_row+8), ': ');
									  $Sheet->setCellValue('C'.($first_row+9), ': ');
									  $Sheet->setCellValue('C'.($first_row+10), ': ');
									  $Sheet->setCellValue('C'.($first_row+11), ': ');
									  
									  
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+7),  $row['kd_mk'].'-'.$row['nm_mk']);
									  //$objPHPExcel->getActiveSheet()->setCellValue('F'.($first_row+8), $ds);
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+10), $row['semkrs'].'/'.$thnsms.'-'.($thnsms+1));
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+11), $nm_shift[$row['shiftkrs']].' ('.$row['kelaskrs'].')');
									  
									  
									  $Sheet->getStyle('A'.($first_row+7).':D'.($first_row+11))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														)
													)
											);
									  
									  
									  $Sheet->setCellValue('A'.($first_row+13),  'NO');
									  $Sheet->mergeCells('A'.($first_row+13).':A'.($first_row+14));
									  $Sheet->setCellValue('B'.($first_row+13), 'NAMA');
									  $Sheet->mergeCells('B'.($first_row+13).':C'.($first_row+14));
									  $Sheet->getStyle('A'.($first_row+13).':C'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+13).':C'.($first_row+14))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  $Sheet->setCellValue('D'.($first_row+13), 'TGL');
									  $Sheet->getStyle('D'.($first_row+13).':D'.($first_row+13))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_RIGHT);
									  $Sheet->setCellValue('D'.($first_row+14), 'NIM');
									  $Sheet->getStyle('D'.($first_row+14).':D'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT); 
									  
									  $Sheet->setCellValue('E'.($first_row+14), '1');
									  $Sheet->setCellValue('F'.($first_row+14), '2');
									  $Sheet->setCellValue('G'.($first_row+14), '3');
									  $Sheet->setCellValue('H'.($first_row+14), '4');
									  $Sheet->setCellValue('I'.($first_row+14), '5');
									  $Sheet->setCellValue('J'.($first_row+14), '6');
									  $Sheet->setCellValue('K'.($first_row+14), '7');
									  $Sheet->setCellValue('L'.($first_row+14), '8');
									  $Sheet->setCellValue('M'.($first_row+14), '9');
									  $Sheet->setCellValue('N'.($first_row+14), '10');
									  $Sheet->setCellValue('O'.($first_row+14), '11');
									  $Sheet->setCellValue('P'.($first_row+14), '12');
									  $Sheet->setCellValue('Q'.($first_row+14), '13');
									  $Sheet->setCellValue('R'.($first_row+14), '14');
									  
									  $Sheet->setCellValue('S'.($first_row+13), 'KET.');
									  $Sheet->mergeCells('S'.($first_row+13).':S'.($first_row+14));
									  
									  $Sheet->getStyle('D'.($first_row+13).':S'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('D'.($first_row+13).':S'.($first_row+14))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  $vbaca_krs = new dt_krs;
									  $sql="fak='".$fak."' and prodi='".$prodi."' and thsmskrs=".$thn. " and semkrs=".$row['semkrs']." and shiftkrs='".$row['shiftkrs']."' and kelaskrs = '".$row['kelaskrs']."' and kampus='".$row['kampus']."' and nokmkkrs='".$row['nokmkkrs']."'";
									  $data_mhs = $vbaca_krs->getMHS1($sql);
									  
									  $i=1;
									  
									  if(!empty($data_mhs))
									  {
									    foreach($data_mhs as $row_mhs)
									    {
										  $Sheet->setCellValue('A'.(($first_row+14)+$i), $i);
										  $Sheet->setCellValue('B'.(($first_row+14)+$i), $row_mhs['Nama_mahasiswa']);
										  $Sheet->mergeCells('B'.(($first_row+14)+$i).':'.'C'.(($first_row+14)+$i));
										  $Sheet->setCellValue('D'.(($first_row+14)+$i), $row_mhs['NIM']);
										  $i++;
										}
									  
									  }
									  
									  for(;$i<=30;$i++){
									    $Sheet->setCellValue('A'.(($first_row+14)+$i), $i);
										$Sheet->mergeCells('B'.(($first_row+14)+$i).':'.'C'.(($first_row+14)+$i));
									  }
									  
									  
									  
									  $Sheet->getStyle('A'.($first_row+15).':A'.(($first_row+14)+$i))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+15).':A'.(($first_row+14)+$i))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  
									  $Sheet->setCellValue('A'.(($first_row+14)+$i), 'TANDA TANGAN DOSEN');
									  $Sheet->mergeCells('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i));
									  $Sheet->getStyle('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  
									  $Sheet->getStyle('A'.($first_row+13).':S'.(($first_row+14)+$i))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														),
														'borders' => array(
															'inside'     => array(
																'style' => PHPExcel_Style_Border::BORDER_THIN
															),
															'outline'     => array(
																'style' => PHPExcel_Style_Border::BORDER_MEDIUM
															)
														)
													)
											);	 
					   
					   
					   
					   
					   
					   
						$Sheet->getPageSetup()->setOrientation(PHPExcel_Worksheet_PageSetup::ORIENTATION_LANDSCAPE);
						$Sheet->getPageSetup()->setPaperSize(PHPExcel_Worksheet_PageSetup::PAPERSIZE_LEGAL);
						//$Sheet->getPageSetup()->setHorizontalCentered(true);
						//$Sheet->getPageSetup()->setVerticalCentered(true);
					   
					   // margin is set in inches (0.5cm)
					  $margin = 0.5 / 2.54;
					  $Sheet->getPageMargins()->setTop($margin);
					  $Sheet->getPageMargins()->setBottom($margin);
					  $Sheet->getPageMargins()->setLeft($margin);
					  $Sheet->getPageMargins()->setRight($margin);
	      
		    $j++;
		  }
	
	      $tmp ="";
		  
		  $base_path = dirname(dirname(__FILE__)). '/cetak/';
		 		 
           $tmp="DHMD ".$vnm_prodi." ".$thn.".xls";
		   
           $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		   $dt_opt_ctk_log->insert($tmp,$id_opt); 

		   
		  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
          $objWriter->save($base_path.$tmp);
	      
          return $tmp;		  
	}
	
	function DHMD_FTI($fak,$prodi,$thn,$id_opt,$data)
	{
	      $nm_shift=array('R'=>'Reguler','N'=>'Non Reguler');
          $objPHPExcel = new PHPExcel();
		  $Sheet = $objPHPExcel->getActiveSheet();
	   
	      
		  //$jml_mtk=$dt_krs->numrows; 
		  
		  $j=0;
		  $first_row=1;
		  foreach($data as $row)
		  {
					   if($j>0)
					   {
					    $Sheet = $objPHPExcel->createSheet($j);						 						 
					   }
					  					  
					  
					   $Sheet->getColumnDimension('A')->setWidth(3.29);
					   $Sheet->getColumnDimension('B')->setWidth(22.29);
					   $Sheet->getColumnDimension('C')->setWidth(1.50);
					   $Sheet->getColumnDimension('D')->setWidth(10.00);
					   $Sheet->getColumnDimension('E')->setWidth(7.00);

					   $Sheet->getColumnDimension('F')->setWidth(7.00);
					   $Sheet->getColumnDimension('G')->setWidth(7.00);
					   $Sheet->getColumnDimension('H')->setWidth(7.00);
					   $Sheet->getColumnDimension('I')->setWidth(7.00);

					   $Sheet->getColumnDimension('J')->setWidth(7.00);
					   $Sheet->getColumnDimension('K')->setWidth(7.00);
					   $Sheet->getColumnDimension('L')->setWidth(7.00);
					   $Sheet->getColumnDimension('M')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('N')->setWidth(7.00);
					   $Sheet->getColumnDimension('O')->setWidth(7.00);
					   $Sheet->getColumnDimension('P')->setWidth(7.00);
					   $Sheet->getColumnDimension('Q')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('R')->setWidth(7.00);
					   $Sheet->getColumnDimension('S')->setWidth(7.00);
					   $Sheet->getColumnDimension('T')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('U')->setWidth(8.00);
					   
					  
									$dt_prodi=new dt_prodi;
									$data = $dt_prodi->getData("kd_fakultas='".$fak."' and kd_prodi='".$prodi."'");
									$vnm_prodi="";
									foreach ($data as $r){						
										  $vnm_prodi=$r['prodi'];						
									}
						
									$dt_fak=new dt_fak;
									$data = $dt_fak->getData("kd_fakultas='".$fak."'");
									$vnm_fak="";
									foreach ($data as $r){						
										  $vnm_fak=$r['fakultas'];						
									}
						  
						
						 
						
									  $Sheet->setCellValue('A'.$first_row, 'PROGRAM STUDI '.strtoupper($vnm_prodi));
									  $Sheet->setCellValue('A'.($first_row+1), strtoupper($vnm_fak));
									  $Sheet->setCellValue('A'.($first_row+2), 'UNIVERSITAS BALE BANDUNG');
									  $Sheet->getStyle('A'.$first_row.':A'.($first_row+2))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														)
													)
											);
									  
									  $Sheet->setCellValue('A'.($first_row+5), 'DAFTAR HADIR MAHASISWA DAN DOSEN (DHMD)');
									  $Sheet->mergeCells('A'.($first_row+5).':U'.($first_row+5));
									  $Sheet->getStyle('A'.($first_row+5).':U'.($first_row+5))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+5).':U'.($first_row+5))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
									  
									  $Sheet->getStyle('A'.($first_row+5).':U'.($first_row+5))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 12
														)
													)
											);		
									  
									  $Sheet->setCellValue('A'.($first_row+7), 'Mata Kuliah');
									  $Sheet->setCellValue('A'.($first_row+8), 'Dosen');
									  $Sheet->setCellValue('A'.($first_row+9), 'Asisten'); 
									  $Sheet->setCellValue('A'.($first_row+10), 'Semester / Tahun Akademik');
									  $Sheet->setCellValue('A'.($first_row+11), 'Kelas');
									  
									   
									   //$thnsms = $vbaca_krs->TA();
									   $tmp = str_split($thn, 4);	  
									   $thnsms=$tmp[0];
									  
									  $Sheet->setCellValue('C'.($first_row+7),  ': ');
									  $Sheet->setCellValue('C'.($first_row+8), ': ');
									  $Sheet->setCellValue('C'.($first_row+9), ': ');
									  $Sheet->setCellValue('C'.($first_row+10), ': ');
									  $Sheet->setCellValue('C'.($first_row+11), ': ');
									  
									  
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+7),  $row['kd_mk'].'-'.$row['nm_mk']);
									  //$objPHPExcel->getActiveSheet()->setCellValue('F'.($first_row+8), $ds);
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+10), $row['semkrs'].'/'.$thnsms.'-'.($thnsms+1));
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+11), $nm_shift[$row['shiftkrs']].' ('.$row['kelaskrs'].')');
									  
									  
									  $Sheet->getStyle('A'.($first_row+7).':D'.($first_row+11))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														)
													)
											);
									  
									  
									  $Sheet->setCellValue('A'.($first_row+13),  'NO');
									  $Sheet->mergeCells('A'.($first_row+13).':A'.($first_row+14));
									  $Sheet->setCellValue('B'.($first_row+13), 'NAMA');
									  $Sheet->mergeCells('B'.($first_row+13).':C'.($first_row+14));
									  $Sheet->getStyle('A'.($first_row+13).':C'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+13).':C'.($first_row+14))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  $Sheet->setCellValue('D'.($first_row+13), 'TGL');
									  $Sheet->getStyle('D'.($first_row+13).':D'.($first_row+13))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_RIGHT);
									  $Sheet->setCellValue('D'.($first_row+14), 'NIM');
									  $Sheet->getStyle('D'.($first_row+14).':D'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_LEFT); 
									  
									  $Sheet->setCellValue('E'.($first_row+14), '1');
									  $Sheet->setCellValue('F'.($first_row+14), '2');
									  $Sheet->setCellValue('G'.($first_row+14), '3');
									  $Sheet->setCellValue('H'.($first_row+14), '4');
									  $Sheet->setCellValue('I'.($first_row+14), '5');
									  $Sheet->setCellValue('J'.($first_row+14), '6');
									  $Sheet->setCellValue('K'.($first_row+14), '7');
									  $Sheet->setCellValue('L'.($first_row+14), '8');
									  $Sheet->setCellValue('M'.($first_row+14), '9');
									  $Sheet->setCellValue('N'.($first_row+14), '10');
									  $Sheet->setCellValue('O'.($first_row+14), '11');
									  $Sheet->setCellValue('P'.($first_row+14), '12');
									  $Sheet->setCellValue('Q'.($first_row+14), '13');
									  $Sheet->setCellValue('R'.($first_row+14), '14');
									  $Sheet->setCellValue('S'.($first_row+14), '15');
									  $Sheet->setCellValue('T'.($first_row+14), '16');
									  
									  $Sheet->setCellValue('U'.($first_row+13), 'KET.');
									  $Sheet->mergeCells('U'.($first_row+13).':U'.($first_row+14));
									  
									  $Sheet->getStyle('D'.($first_row+13).':U'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('D'.($first_row+13).':U'.($first_row+14))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  $vbaca_krs = new dt_krs;
									  $sql="fak='".$fak."' and prodi='".$prodi."' and thsmskrs=".$thn. " and semkrs=".$row['semkrs']." and shiftkrs='".$row['shiftkrs']."' and kelaskrs = '".$row['kelaskrs']."' and kampus='".$row['kampus']."' and nokmkkrs='".$row['nokmkkrs']."'";
									  $data_mhs = $vbaca_krs->getMHS1($sql);
									  
									  $i=1;
									  
									  if(!empty($data_mhs))
									  {
									    foreach($data_mhs as $row_mhs)
									    {
										  $Sheet->setCellValue('A'.(($first_row+14)+$i), $i);
										  $Sheet->setCellValue('B'.(($first_row+14)+$i), $row_mhs['Nama_mahasiswa']);
										  $Sheet->mergeCells('B'.(($first_row+14)+$i).':'.'C'.(($first_row+14)+$i));
										  $Sheet->setCellValue('D'.(($first_row+14)+$i), $row_mhs['NIM']);
										  $i++;
										}
									  
									  }
									  
									  for(;$i<=20;$i++){
									    $Sheet->setCellValue('A'.(($first_row+14)+$i), $i);
										$Sheet->mergeCells('B'.(($first_row+14)+$i).':'.'C'.(($first_row+14)+$i));
									  }
									  
									  
									  
									  $Sheet->getStyle('A'.($first_row+15).':A'.(($first_row+14)+$i))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+15).':A'.(($first_row+14)+$i))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  
									  $Sheet->setCellValue('A'.(($first_row+14)+$i), 'TANDA TANGAN DOSEN');
									  $Sheet->mergeCells('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i));
									  $Sheet->getStyle('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  
									  $Sheet->getStyle('A'.($first_row+13).':U'.(($first_row+14)+$i))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														),
														'borders' => array(
															'inside'     => array(
																'style' => PHPExcel_Style_Border::BORDER_THIN
															),
															'outline'     => array(
																'style' => PHPExcel_Style_Border::BORDER_MEDIUM
															)
														)
													)
											);	 
					   
					   
					   
					   
					   
					   
						$Sheet->getPageSetup()->setOrientation(PHPExcel_Worksheet_PageSetup::ORIENTATION_LANDSCAPE);
						$Sheet->getPageSetup()->setPaperSize(PHPExcel_Worksheet_PageSetup::PAPERSIZE_LEGAL);
						//$Sheet->getPageSetup()->setHorizontalCentered(true);
						//$Sheet->getPageSetup()->setVerticalCentered(true);
					   
					   // margin is set in inches (0.5cm)
					  $margin = 0.5 / 2.54;
					  $Sheet->getPageMargins()->setTop($margin);
					  $Sheet->getPageMargins()->setBottom($margin);
					  $Sheet->getPageMargins()->setLeft($margin);
					  $Sheet->getPageMargins()->setRight($margin);
	      
		    $j++;
		  }
	
	      $tmp ="";
		  
		  $base_path = dirname(dirname(__FILE__)). '/cetak/';
		 		 
           $tmp="DHMD ".$vnm_prodi." ".$thn.".xls";
		    
		   $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		   $dt_opt_ctk_log->insert($tmp,$id_opt);	
			
		  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
          $objWriter->save($base_path.$tmp);
	      
          return $tmp;		  
	}
	function DHMD_FIKES($fak,$prodi,$thn,$id_opt,$data)
	{
	      $nm_shift=array('R'=>'Reguler','N'=>'Non Reguler');
          $objPHPExcel = new PHPExcel();
		  $Sheet = $objPHPExcel->getActiveSheet();
	   
	      
		  //$jml_mtk=$dt_krs->numrows; 
		  
		  $j=0;
		  $first_row=1;
		  foreach($data as $row)
		  {
					   if($j>0)
					   {
					    $Sheet = $objPHPExcel->createSheet($j);						 						 
					   }
					  					  
					  
					   $Sheet->getColumnDimension('A')->setWidth(3.29);
					   $Sheet->getColumnDimension('B')->setWidth(22.29);
					   $Sheet->getColumnDimension('C')->setWidth(1.50);
					   $Sheet->getColumnDimension('D')->setWidth(10.00);
					   $Sheet->getColumnDimension('E')->setWidth(7.00);

					   $Sheet->getColumnDimension('F')->setWidth(7.00);
					   $Sheet->getColumnDimension('G')->setWidth(7.00);
					   $Sheet->getColumnDimension('H')->setWidth(7.00);
					   $Sheet->getColumnDimension('I')->setWidth(7.00);

					   $Sheet->getColumnDimension('J')->setWidth(7.00);
					   $Sheet->getColumnDimension('K')->setWidth(7.00);
					   $Sheet->getColumnDimension('L')->setWidth(7.00);
					   $Sheet->getColumnDimension('M')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('N')->setWidth(7.00);
					   $Sheet->getColumnDimension('O')->setWidth(7.00);
					   $Sheet->getColumnDimension('P')->setWidth(7.00);
					   $Sheet->getColumnDimension('Q')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('R')->setWidth(7.00);
					   $Sheet->getColumnDimension('S')->setWidth(7.00);
					   $Sheet->getColumnDimension('T')->setWidth(7.00);
					   
					   $Sheet->getColumnDimension('U')->setWidth(8.00);
					   
					  
									$dt_prodi=new dt_prodi;
									$data = $dt_prodi->getData("kd_fakultas='".$fak."' and kd_prodi='".$prodi."'");
									$vnm_prodi="";
									foreach ($data as $r){						
										  $vnm_prodi=$r['prodi'];						
									}
						
									$dt_fak=new dt_fak;
									$data = $dt_fak->getData("kd_fakultas='".$fak."'");
									$vnm_fak="";
									foreach ($data as $r){						
										  $vnm_fak=$r['fakultas'];						
									}
						  
						
						 
						
									  $Sheet->setCellValue('A'.$first_row, 'PROGRAM STUDI '.strtoupper($vnm_prodi));
									  $Sheet->setCellValue('A'.($first_row+1), strtoupper($vnm_fak));
									  $Sheet->setCellValue('A'.($first_row+2), 'UNIVERSITAS BALE BANDUNG');
									  $Sheet->getStyle('A'.$first_row.':A'.($first_row+2))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														)
													)
											);
									  
									  $Sheet->setCellValue('A'.($first_row+5), 'DAFTAR HADIR MAHASISWA DAN DOSEN (DHMD)');
									  $Sheet->mergeCells('A'.($first_row+5).':U'.($first_row+5));
									  $Sheet->getStyle('A'.($first_row+5).':U'.($first_row+5))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+5).':U'.($first_row+5))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER); 		
									  
									  $Sheet->getStyle('A'.($first_row+5).':U'.($first_row+5))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 12
														)
													)
											);		
									  
									  $Sheet->setCellValue('A'.($first_row+7), 'Mata Kuliah');
									  $Sheet->setCellValue('A'.($first_row+8), 'Dosen');
									  $Sheet->setCellValue('A'.($first_row+9), 'Asisten'); 
									  $Sheet->setCellValue('A'.($first_row+10), 'Semester / Tahun Akademik');
									  $Sheet->setCellValue('A'.($first_row+11), 'Kelas');
									  
									   
									   //$thnsms = $vbaca_krs->TA();
									   $tmp = str_split($thn, 4);	  
									   $thnsms=$tmp[0];
									  
									  $Sheet->setCellValue('C'.($first_row+7),  ': ');
									  $Sheet->setCellValue('C'.($first_row+8), ': ');
									  $Sheet->setCellValue('C'.($first_row+9), ': ');
									  $Sheet->setCellValue('C'.($first_row+10), ': ');
									  $Sheet->setCellValue('C'.($first_row+11), ': ');
									  
									  
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+7),  $row['kd_mk'].'-'.$row['nm_mk']);
									  //$objPHPExcel->getActiveSheet()->setCellValue('F'.($first_row+8), $ds);
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+10), $row['semkrs'].'/'.$thnsms.'-'.($thnsms+1));
									  $objPHPExcel->getActiveSheet()->setCellValue('D'.($first_row+11), $nm_shift[$row['shiftkrs']].' ('.$row['kelaskrs'].')');
									  
									  
									  $Sheet->getStyle('A'.($first_row+7).':D'.($first_row+11))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														)
													)
											);
									  
									  
									  $Sheet->setCellValue('A'.($first_row+13),  'NO');
									  $Sheet->mergeCells('A'.($first_row+13).':A'.($first_row+14));
									  $Sheet->setCellValue('B'.($first_row+13), 'NAMA');
									  $Sheet->mergeCells('B'.($first_row+13).':C'.($first_row+14));
									  $Sheet->getStyle('A'.($first_row+13).':C'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+13).':C'.($first_row+14))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  $Sheet->setCellValue('D'.($first_row+13), 'NIM');
									  $Sheet->mergeCells('D'.($first_row+13).':D'.($first_row+14));
									  $Sheet->getStyle('D'.($first_row+13).':D'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('D'.($first_row+13).':D'.($first_row+14))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  $Sheet->setCellValue('E'.($first_row+13), 'PERTEMUAN');
									  $Sheet->mergeCells('E'.($first_row+13).':T'.($first_row+13));
									  $Sheet->getStyle('E'.($first_row+13).':T'.($first_row+13))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('E'.($first_row+13).':T'.($first_row+13))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  
									  $Sheet->setCellValue('E'.($first_row+14), '1');
									  $Sheet->setCellValue('F'.($first_row+14), '2');
									  $Sheet->setCellValue('G'.($first_row+14), '3');
									  $Sheet->setCellValue('H'.($first_row+14), '4');
									  $Sheet->setCellValue('I'.($first_row+14), '5');
									  $Sheet->setCellValue('J'.($first_row+14), '6');
									  $Sheet->setCellValue('K'.($first_row+14), '7');
									  $Sheet->setCellValue('L'.($first_row+14), 'UTS');
									  $Sheet->setCellValue('M'.($first_row+14), '9');
									  $Sheet->setCellValue('N'.($first_row+14), '10');
									  $Sheet->setCellValue('O'.($first_row+14), '11');
									  $Sheet->setCellValue('P'.($first_row+14), '12');
									  $Sheet->setCellValue('Q'.($first_row+14), '13');
									  $Sheet->setCellValue('R'.($first_row+14), '14');
									  $Sheet->setCellValue('S'.($first_row+14), '15');
									  $Sheet->setCellValue('T'.($first_row+14), 'UAS');
									  
									  $Sheet->setCellValue('U'.($first_row+13), 'KET.');
									  $Sheet->mergeCells('U'.($first_row+13).':U'.($first_row+14));
									  
									  $Sheet->getStyle('D'.($first_row+13).':U'.($first_row+14))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('D'.($first_row+13).':U'.($first_row+14))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  $vbaca_krs = new dt_krs;
									  $sql="fak='".$fak."' and prodi='".$prodi."' and thsmskrs=".$thn. " and semkrs=".$row['semkrs']." and shiftkrs='".$row['shiftkrs']."' and kelaskrs = '".$row['kelaskrs']."' and kampus='".$row['kampus']."' and nokmkkrs='".$row['nokmkkrs']."'";
									  $data_mhs = $vbaca_krs->getMHS1($sql);
									  
									  $i=1;
									  
									  if(!empty($data_mhs))
									  {
									    foreach($data_mhs as $row_mhs)
									    {
										  $Sheet->setCellValue('A'.(($first_row+14)+$i), $i);
										  $Sheet->setCellValue('B'.(($first_row+14)+$i), $row_mhs['Nama_mahasiswa']);
										  $Sheet->mergeCells('B'.(($first_row+14)+$i).':'.'C'.(($first_row+14)+$i));
										  $Sheet->setCellValue('D'.(($first_row+14)+$i), $row_mhs['NIM']);
										  $i++;
										}
									  
									  }
									  
									  for(;$i<=20;$i++){
									    $Sheet->setCellValue('A'.(($first_row+14)+$i), $i);
										$Sheet->mergeCells('B'.(($first_row+14)+$i).':'.'C'.(($first_row+14)+$i));
									  }
									  
									  
									  
									  $Sheet->getStyle('A'.($first_row+15).':A'.(($first_row+14)+$i))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.($first_row+15).':A'.(($first_row+14)+$i))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  
									  $Sheet->setCellValue('A'.(($first_row+14)+$i), 'JUMLAH HADIR');
									  $Sheet->mergeCells('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i));
									  $Sheet->getStyle('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.(($first_row+14)+$i).':D'.(($first_row+14)+$i))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  $Sheet->setCellValue('A'.(($first_row+15)+$i), 'PARAF DOSEN');
									  $Sheet->mergeCells('A'.(($first_row+15)+$i).':D'.(($first_row+15)+$i));
									  $Sheet->getStyle('A'.(($first_row+15)+$i).':D'.(($first_row+15)+$i))->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER); 
									  $Sheet->getStyle('A'.(($first_row+15)+$i).':D'.(($first_row+15)+$i))->getAlignment()->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
									  
									  
									  $Sheet->getStyle('A'.($first_row+13).':U'.(($first_row+15)+$i))->applyFromArray(
													array(
														'font'    => array(
															'bold'      => true,
															'name'      => 'Times New Roman',
															'size'      => 10
														),
														'borders' => array(
															'inside'     => array(
																'style' => PHPExcel_Style_Border::BORDER_THIN
															),
															'outline'     => array(
																'style' => PHPExcel_Style_Border::BORDER_MEDIUM
															)
														)
													)
											);	 
					   
					   
					   
					   
					   
					   
						$Sheet->getPageSetup()->setOrientation(PHPExcel_Worksheet_PageSetup::ORIENTATION_LANDSCAPE);
						$Sheet->getPageSetup()->setPaperSize(PHPExcel_Worksheet_PageSetup::PAPERSIZE_LEGAL);
						//$Sheet->getPageSetup()->setHorizontalCentered(true);
						//$Sheet->getPageSetup()->setVerticalCentered(true);
					   
					   // margin is set in inches (0.5cm)
					  $margin = 0.5 / 2.54;
					  $Sheet->getPageMargins()->setTop($margin);
					  $Sheet->getPageMargins()->setBottom($margin);
					  $Sheet->getPageMargins()->setLeft($margin);
					  $Sheet->getPageMargins()->setRight($margin);
	      
		    $j++;
		  }
	
	      $tmp ="";
		  
		  $base_path = dirname(dirname(__FILE__)). '/cetak/';
		 		 
           $tmp="DHMD ".$vnm_prodi." ".$thn.".xls";
		    
		   $dt_opt_ctk_log = new dt_opt_ctk_log;		  
		   $dt_opt_ctk_log->insert($tmp,$id_opt);	
			
		  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel5');
          $objWriter->save($base_path.$tmp);
	      
          return $tmp;		  
	}
	
	function DHMD_to_excel($fak,$prodi,$thn,$id_opt)
	{
	    
		
		$sql="kd_fakultas='".$fak."' and kd_prodi='".$prodi."' and thsmskrs=".$thn;
		$dt_krs=new dt_krs;
		$data = $dt_krs->getMTK($sql);
	   
   	    $ada_data=0;
	    
		$tmp="";
	   if(!empty($data)){
		 $ada_data=1;
		 if($fak=='FKIP'){
		   $tmp=$this->DHMD_FKIP($fak,$prodi,$thn,$id_opt,$data);
	     }
		 if($fak=='FTI'){
		   $tmp=$this->DHMD_FTI($fak,$prodi,$thn,$id_opt,$data);
	     }
		 if($fak=='FIKES'){
		   $tmp=$this->DHMD_FIKES($fak,$prodi,$thn,$id_opt,$data);
	     }
	   }  
	  	  
		
		if($ada_data==1){
         $base_path = dirname(dirname(__FILE__)). '/cetak/';
         if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }      		  
		 	 
		  return $base_path.$tmp;
		 }else
		 {
		   return 0;
		 
		 }		
	}
	
}
?>












