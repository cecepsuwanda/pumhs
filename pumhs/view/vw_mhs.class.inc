<?php

class vw_mhs
{  
    var $dt_mhs;
	var $dt_mhs_epsbed;
	var $syarat;
	var $nm_tb;
	
	function __construct()
	{ 	
        $this->dt_mhs = new dt_mhs;
        $this->dt_mhs_epsbed = new dt_mhs_epsbed;
                 
				 $this->syarat['ktp']['pjg']=16;
				 $this->syarat['ktp']['pjg_msg']="Panjang No KTP kurang dari 16 angka, silakan daftar ulang dengan No KTP yang benar !!!";
				 $this->syarat['ktp']['pattern1']="/[1 3][1-8][0-2 7][0-9][0-4][0-9][0-7][0-9][0-1][0-9][0-1 5-9][0-9]{4}/";
				 $this->syarat['ktp']['pattern2']="/12345[0-6][0-9]{8}/";
				 $this->syarat['ktp']['pattern_msg']="PUMHS tidak mengenali format nomor KTP anda, untuk penjelasan lebih lanjut hubungi operator PUMHS di fakultas masing-masing !!! ";
				 
				 
				 $this->syarat['nim']['pattern']="/[A-Ga-g]1[A-Ga-g][0-9]{6}/";
				 $this->syarat['nim']['msg']="NIM salah tulis !!!";
		         $this->syarat['nim']['fak']['FAPERTA']['pattern']="/[Aa]1[A-Ca-c][0-9]{6}/";
				 $this->syarat['nim']['fak']['FAPERTA']['msg']="Bukan NIM Fakultas Pertanian !!!";
				 $this->syarat['nim']['fak']['FAPERTA']['prodi']['AGB']['pattern']="/[Aa]1[Bb][0-9]{6}/";
				 $this->syarat['nim']['fak']['FAPERTA']['prodi']['AGB']['msg']="Bukan NIM Prodi Agribisnis !!!";
				 $this->syarat['nim']['fak']['FAPERTA']['prodi']['AGT']['pattern']="/[Aa]1[Aa][0-9]{6}/";
				 $this->syarat['nim']['fak']['FAPERTA']['prodi']['AGT']['msg']="Bukan NIM Prodi Agroteknologi !!!";
				 $this->syarat['nim']['fak']['FAPERTA']['prodi']['TP']['pattern']="/[Aa]1[Cc][0-9]{6}/";
				 $this->syarat['nim']['fak']['FAPERTA']['prodi']['TP']['msg']="Bukan NIM Prodi Teknologi Pangan !!!";
				 				 				 
				 $this->syarat['nim']['fak']['FE']['pattern']="/[Ee]1[Aa][0-9]{6}/";
				 $this->syarat['nim']['fak']['FE']['msg']="Bukan NIM Fakultas Ekonomi !!!";
				 				 
                 $this->syarat['nim']['fak']['FISIP']['pattern']="/[Dd]1[Aa][0-9]{6}/";
				 $this->syarat['nim']['fak']['FISIP']['msg']="Bukan NIM FISIP !!!";
				 
				 $this->syarat['nim']['fak']['FIKES']['pattern']="/[Gg]1[Aa][0-9]{6}/";
				 $this->syarat['nim']['fak']['FIKES']['msg']="Bukan NIM Fakultas Kesehatan !!!";
				 				 
				 $this->syarat['nim']['fak']['FTI']['pattern']="/[Cc]1[A-Ba-b][0-9]{6}/";
                 $this->syarat['nim']['fak']['FTI']['msg']="Bukan NIM Fakultas Teknologi Informasi !!!"; 				 
				 $this->syarat['nim']['fak']['FTI']['prodi']['IF']['pattern']="/[Cc]1[Aa][0-9]{6}/";
				 $this->syarat['nim']['fak']['FTI']['prodi']['IF']['msg']="Bukan NIM Prodi Informatika !!!";
				 $this->syarat['nim']['fak']['FTI']['prodi']['SI']['pattern']="/[Cc]1[Bb][0-9]{6}/";
				 $this->syarat['nim']['fak']['FTI']['prodi']['SI']['msg']="Bukan NIM Prodi Sistem Informasi !!!";				 
								 
								 
				 $this->syarat['nim']['fak']['FKIP']['pattern']="/[Bb]1[A-Da-d][0-9]{6}/";
				 $this->syarat['nim']['fak']['FKIP']['msg']="Bukan NIM FKIP !!!";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['GEO']['pattern']="/[Bb]1[Aa][0-9]{6}/";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['GEO']['msg']="Bukan NIM Prodi Geografi !!!";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['ING']['pattern']="/[Bb]1[Bb][0-9]{6}/";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['ING']['msg']="Bukan NIM Prodi Bahasa Inggris !!!";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['IND']['pattern']="/[Bb]1[Cc][0-9]{6}/";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['IND']['msg']="Bukan NIM Prodi Bahasa Indonesia !!!";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['IPS']['pattern']="/[Bb]1[Dd][0-9]{6}/";
				 $this->syarat['nim']['fak']['FKIP']['prodi']['IPS']['msg']="Bukan NIM Prodi IPS !!!";			 
				 
				 $this->syarat['nim']['fak']['FMIPA']['pattern']="/[Ff]1[Aa][0-9]{6}/";
				 $this->syarat['nim']['fak']['FMIPA']['msg']="Bukan NIM Fakultas MIPA !!!";
                  
		         $this->nm_tb = array(1=>'tb_create',2=>'tb_update',3=>'tb_login');   
	}
	
	
	
	
	
	function validasi($row)
	{  $txt="";
	   $tmp_date =date("Y");  

           if(strlen($row['NO_KTP'])<$this->syarat['ktp']['pjg']){					
			   $txt = $txt."<li>".$this->syarat['ktp']['pjg_msg']."</li>";
			}else{			  	
				if(preg_match($this->syarat['ktp']['pattern1'],$row['NO_KTP'])==0){
				   if(preg_match($this->syarat['ktp']['pattern2'],$row['NO_KTP'])==0){
					   $txt = $txt."<li>".$this->syarat['ktp']['pattern_msg']."</li>";
				  }
				}

                if($row['Tanggal_lahir']=="0000-00-00"){
					$txt = $txt."<li>Tanggal lahir harap diisi !!!</li>";
				}  
				else{ 
					 $parts = explode("-",$row['Tanggal_lahir']);
					
					 $tmp = intval($parts[2]) % 10;
					 $tmp = $tmp.$parts[1].(substr($parts[0],-2));
					
  					 $tmp1 = substr($row['NO_KTP'],7,5);
					
					 if($tmp!=$tmp1)
					 {
					   $txt = $txt."<li>Tanggal lahir tidak sesuai KTP, silakan login untuk memperbaiki !!!</li>";
					 }else 
					 {
					    if(($row['Tgl_Log']==null) and ($row['optcid']==null) and ($row['optuid']==null) )
                           {$txt = $txt."<li>Silahkan login untuk melengkapi data !!!</li>";}				
				        else
						{
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
							        if( ($row['Tahun_masuk']!="0000") && ($row['Tanggal_masuk'] != null) && ($parts[0]!=$row['Tahun_masuk']))
							        {
									  if($row['Tanggal_masuk'] == "0000-00-00"){
                                         $tmp_tgl=$row['Tahun_masuk']."-09-23";	
                                      }									
								       else {
  								         $tmp_tgl=$row['Tahun_masuk'].'-'.$parts[1].'-'.$parts[2]; 
									  }
								  
								      if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){
								          $this->dt_mhs->update_tgl_msk($row['NO_KTP'],$tmp_tgl);
								      }
									  //$txt = $txt."<li>Tahun  Masuk dan Tanggal Masuk tak sesuai</li>";
									}

                                     if(($row['NIM']=="")){
                                        if ($row['Tahun_masuk']<$tmp_date) {
										    $txt = $txt."<li>NIM mohon diisi</li>";
						                    $cek_nim=1;
										} else {
						                    $cek_nim=1;
						                }
                                     }else{
									    $cek_nim=0;
									    if(preg_match($this->syarat['nim']['pattern'],$row['NIM'])==0){
											  $txt = $txt."<li>".$this->syarat['nim']['msg']."</li>";
											  $cek_nim=1;
										}else{
										       if((preg_match( $this->syarat['nim']['fak'][$row['kd_fakultas']]['pattern'],$row['NIM'])==0)){
												  $txt = $txt."<li>".$this->syarat['nim']['fak'][$row['kd_fakultas']]['msg']."</li>";
												  $cek_nim=1;
											   } else {
											       if( isset($this->syarat['nim']['fak'][$row['kd_fakultas']]['prodi'][$row['kd_prodi']]['pattern']) && (preg_match( $this->syarat['nim']['fak'][$row['kd_fakultas']]['prodi'][$row['kd_prodi']]['pattern'],$row['NIM'])==0)){
														  $txt = $txt."<li>".$this->syarat['nim']['fak'][$row['kd_fakultas']]['prodi'][$row['kd_prodi']]['msg']."</li>";
														  $cek_nim=1;
													   }											       
											   } 
										
										} 
									 }

                                     if($cek_nim==0){
												
											  $tmp1=substr($row['NIM'],4,1);
											  $tmp2=substr($row['Tahun_masuk'],3,1);
												 if(strcmp($tmp1,$tmp2)!=0) {
												   $txt = $txt."<li>Tahun  Masuk dan NIM tak sesuai</li>";
												 } 
																					 
										 }										 
								 
								 }
							 }
							 
							 
							 
						}
					 
					 
					 }
					 
					 
					 
					}      

                     					

				
			}	
               
			if($txt=="")
			{
			              $txt = "<li>Data Lengkap</li>";
						
                          //if($row['verifikasi']==1){ 
						    //  if($this->dt_mhs->is_nim_double($row['NIM']))
						      //{
						        //$txt .= "<li>NIM Double !!!</li>";
						      //}
						      //if($this->dt_mhs->is_nm_double(addslashes($row['Nama_mahasiswa'])))
							  //{
								//$txt .= "<li>Nama Double !!!</li>";
							  //}
						   //}
						   
						  if($row['validasi']==0){ 
							$this->dt_mhs->update_validasi($row['NO_KTP'],1);
						  } 	
							//if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){
 							 if( $row['verifikasi']==0 and $row['kd_fakultas']=='FTI' and $row['kd_fakultas']=='FE' and $row['kd_fakultas']=='FMIPA'){
								   if($this->dt_mhs_epsbed->is_exist($row['NIM'],addslashes($row['Nama_mahasiswa']))){
								   $optudate= date("Y-m-d H:i:s");
								   $this->dt_mhs->update_verifikasi($row['NO_KTP'],1,$optudate,"System");							
								  }	
								} 				  
							 //}
						   
			}else
			{
			             
						 if(($txt=="<li>NIM mohon diisi</li>") && (($row['NIM']=="") &&( in_array($row['Tahun_masuk'],array(2013,2014)))))
                          {
						      
							  $txt = "<li>Data Lengkap</li>";
							  
							  //if($row['verifikasi']==1){ 
							    //  if($this->dt_mhs->is_nm_double(addslashes($row['Nama_mahasiswa'])))
								  //{
									//$txt .= "<li>Nama Double !!!</li>";
								  //}	
							  //}						  
							  
                           if($row['validasi']==0){ 						    
							$this->dt_mhs->update_validasi($row['NO_KTP'],1);
                           }
						   //if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){                            
							if($row['verifikasi']==0 and (in_array($row['kd_fakultas'],array('FTI','FE','FMIPA'))) ) {
							   if($this->dt_mhs_epsbed->is_exist($row['NIM'],addslashes($row['Nama_mahasiswa']))){
								   $optudate= date("Y-m-d H:i:s");
								   $this->dt_mhs->update_verifikasi($row['NO_KTP'],1,$optudate,"System");							
							   }
                              }							   
						    //}
						  }else{						  
						    
							if($row['verifikasi']==1){
							  $txt.="<li>Data anda diverifikasi Prodi, Perbaiki Kekurangannya </li>";
							}
							if(date("Y-m-d",strtotime($row['mhsudate']))==date("Y-m-d")){ 						       
							   $this->dt_mhs->update_validasi($row['NO_KTP'],0);
						    }
						   }
			
			}
						   
			   
			   
			
	    return $txt;
	}
	
	
	private function ismrhitl($id_opt,$data)
	{
	   if($id_opt<>''){
	      return "<font color='green'><i>".$data."</i></font>";
	   }else{
	      return "$data";
	   }
	}
	
	function lst_entry_data($idx=0,$id="lst_mhs")
	{
	 

     $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => $id,"width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('Fak. - Prodi', null, 'header');
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('NIM', null, 'header');
        $tbl->addCell('Tahun Masuk', null, 'header');		
      	
		$tbl->addCell('Validasi', null, 'header');
				
		
		

        
		$data = $this->dt_mhs->getDataView($idx); 
		if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		    $txt=''; 
		    $txt=$this->validasi($row);		    
		 	
		   
			$i=$i+1;
			$tbl->addRow();        
		    $tbl->addCell($this->ismrhitl($row['optcid'],$i), null, 'data');
		    $tbl->addCell($this->ismrhitl($row['optcid'],$row['kd_fakultas'].'-'.$row['prodi']), null, 'data');
		    $tbl->addCell($this->ismrhitl($row['optcid'],strtoupper($row['Nama_mahasiswa'])), null, 'data');
		    $tbl->addCell($this->ismrhitl($row['optcid'],$row['NIM']), null, 'data');
		    $tbl->addCell($this->ismrhitl($row['optcid'],$row['Tahun_masuk']), null, 'data');		           
		    $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
			
		}
		  
		 
      }
	 
	 return $tbl->display("");
	}
	
	function entry_data2($idx=0,$fak='')
	{
	    		
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => $this->nm_tb[$idx],"width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('Fak. - Prodi', null, 'header');
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('NIM', null, 'header');	    
        $tbl->addCell('Tahun Masuk', null, 'header');
		if ($idx==2)
		{
		$tbl->addCell('Validasi', null, 'header');
		}
		
		
		$data = $this->dt_mhs->getActivitasHariIni($idx);
		
		
	  if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  $i=$i+1;
		  $tbl->addRow();        
		  $tbl->addCell($i, null, 'data');
	      $tbl->addCell($row['kd_fakultas'].'-'.$row['prodi'], null, 'data');
		  $tbl->addCell(strtoupper($row['Nama_mahasiswa']), null, 'data');
     	  $tbl->addCell($row['NIM'], null, 'data'); 
		  $tbl->addCell($row['Tahun_masuk'], null, 'data');
			if ($idx==2)
		    {
		      $txt=$this->validasi($row);
			  $tbl->addCell("<FONT SIZE='1'><ul>".$txt."</ul></FONT>", null, 'data');
		    }     
			   			 
          }
		  
		 
      }
                 
					
	  return $tbl->display("");
	}
	
	function activitas_hari_ini()
	{
	    $txt="<fieldset>";
        $txt=$txt."<legend>Mahasiswa Login Hari Ini:</legend>";  
        $txt=$txt."<div>";  
         	 
	    $txt=$txt.$this->entry_data2(3);
        $txt=$txt."</div>";	
        $txt=$txt."</fieldset>"; 
		
		$txt=$txt."<fieldset>";
        $txt=$txt."<legend>Mahasiswa Update Data Hari Ini:</legend>";  
        $txt=$txt."<div>";          	
	    $txt=$txt.$this->entry_data2(2);
        $txt=$txt."</div>";	
        $txt=$txt."</fieldset>";
		
		$txt=$txt."<fieldset>";
        $txt=$txt."<legend>Mahasiswa Buat Akun Hari Ini:</legend>";  
        $txt=$txt."<div>";  
         	 
	    $txt=$txt.$this->entry_data2(1);
        $txt=$txt."</div>";	
        $txt=$txt."</fieldset>";
	
	    return $txt;
	}
	
	function entry_data1()
	{
	    	$txt1='<div id="tabs1">';
			$txt1.='<ul>';
			$txt1.='<li><a href="#tabs-11" onClick="ch_cont_tab(1);">Log Mahasiswa</a></li>';
			$txt1.='<li><a href="#tabs-21" onClick="ch_cont_tab(2);" >Data Belum Layak Verifikasi</a></li>';
			$txt1.='<li><a href="#tabs-31" onClick="ch_cont_tab(3);">Data Layak Verifikasi</a></li>';
			$txt1.='<li><a href="#tabs-41" onClick="ch_cont_tab(4);">Data Sedang Diverifikasi</a></li>';
			$txt1.='<li><a href="#tabs-51" onClick="ch_cont_tab(5);">Data Lolos Verifikasi</a></li>';
			$txt1.='<li><a href="#tabs-61" onClick="ch_cont_tab(6);">Data Tidak Lolos Verifikasi</a></li>';			
			$txt1.='</ul>';
			
			
			$txt1.='<div id="tabs-11">';
				$txt1.="<div  id='data1'>";
				$txt1.="<fieldset>";
				$txt1.="<legend>Keterangan :</legend>";
				$txt1.="1. Data belum layak verifikasi dikarenakan hasil validasi menyatakan data belum lengkap. <br>";
				$txt1.="2. Data layak verifikasi dikarenakan hasil validasi menyatakan data lengkap. <br>";
				$txt1.="3. Data lolos verifikasi bila Program Studi mengakui kebenaran data yang diinput. <br>";
				$txt1.="4. Data tidak lolos verifikasi bila Program Studi tidak mengakui kebenaran data yang diinput. <br>";
				$txt1.="5. Data yang diberi warna, diinput oleh operator fakultas, hanya operator fakultas yang bisa merubah data tersebut. <br>";
				$txt1.="</fieldset><br>";
				$txt1.="<fieldset>";
				$txt1.=$this->activitas_hari_ini();
				$txt1.="</fieldset>";
				$txt1.="</div>";
			$txt1.='</div>';
			
			
			$txt1.='<div id="tabs-21">';
			$txt1.="<div  id='data2'></div>";
			
			$txt1.='</div>';
			$txt1.='<div id="tabs-31">';
			$txt1.="<div  id='data3'></div>";
			
			
			$txt1.='</div>';
			$txt1.='<div id="tabs-41">';
			$txt1.="<div  id='data4'></div>";
			
			
			$txt1.='</div>';
			$txt1.='<div id="tabs-51">';
			$txt1.="<div  id='data5'></div>";
			
			
			$txt1.='</div>';
			
			$txt1.='<div id="tabs-61">';
			$txt1.="<div  id='data6'></div>";
			$txt1.='</div>';
			$txt1.='</div>';
                 
			$txt2='<div id="tabs2">';
			$txt2.='<ul>';
			$txt2.='<li><a href="#tabs-12" onClick="ch_cont_tab(7);">Daftar Mahasiswa</a></li>';
			$txt2.='<li><a href="#tabs-22" onClick="ch_cont_tab(8);" >Daftar Matakuliah</a></li>';
			$txt2.='</ul>';
			
			
			$txt2.='<div id="tabs-12">';
		    $txt2.="<div  id='data7'>";
			//$vwkrs = new vw_krs; 
            //$txt2.= $vwkrs->list_mhs();	
			$txt2.="</div>";			
			$txt2.='</div>';
			$txt2.='<div id="tabs-22">';
			$txt2.="<div  id='data8'></div>";
            		
			$txt2.='</div>';
			$txt2.='</div>';
			
			$txt='<div id="tabs">';
			$txt.='<ul>';
			$txt.='<li><a href="#tabs-1" >Data PUMHS</a></li>';
			$txt.='<li><a href="#tabs-2" >Data KRS Online</a></li>';
			$txt.='</ul>';
			$txt.='<div id="tabs-1">';	
			$txt.=$txt1;
			$txt.='</div>';
			$txt.='<div id="tabs-2">';
			$txt.=$txt2;			
			$txt.='</div>';
			$txt.='</div>';
			
			$txt="<fieldset>"."<legend>Data yang sudah masuk :</legend>".$txt1."</fieldset>";
	   return $txt;
	}
	
	
	
	
	
	
}
?>












