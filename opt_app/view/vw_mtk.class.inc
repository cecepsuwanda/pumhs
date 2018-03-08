<?php

class vw_mtk
{  
    var $dt_mtk;
	function __construct()	{
	  	$this->dt_mtk = new dt_mtk;		
	}
	function filter_prodi()
	{
	
	         $txt1='<select name="Prodi" id="Prodi">';
					$dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("");
					$vkd_prodi="";
					$vnm_prodi="";
					foreach ($data as $r){
						if($vkd_prodi=="")
						{
						  $vkd_prodi=$r['kd_prodi'];
						  $vnm_prodi=$r['prodi'];
						  $txt1.= "<option selected='selected' value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
						else{
						$txt1.= "<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>";
						}
					}

                $txt1.='</select>';
				
	  $txt = "<fieldset>";
	  $txt.= "<legend>Filter Prodi.</legend>";
      $txt.= "Fak. - Prodi : ".$txt1."<button onclick='filter_mtk()'>Filter</button>";
      $txt.= "</fieldset>";	  
	  $txt.= "<div id='hsl_filter'>".$this->hsl_filter_prodi($vkd_prodi)."</div>";			
				
	  return $txt;
	}
	
	function hsl_filter_prodi($kd_prodi)
	{
	   
	   $dt_prodi=new dt_prodi;
	   $data = $dt_prodi->getData('kd_prodi="'.$kd_prodi.'"');
	   
	   foreach ($data as $r){
	     $vnm_prodi=$r['prodi'];
	   }
	   
	   $txt = "<fieldset>";
	   $txt.= "<legend>Prodi.".$vnm_prodi."</legend>";
       
	   if($kd_prodi=='AGB'){
	      $txt.= $this->kur_AGB();
	   }else{                                                     
              if($kd_prodi=='AGT'){
			   $txt.= $this->kur_AGT();
		      }else{
			    if($kd_prodi=='AK'){
			       $txt.= $this->kur_AK();
			    }else {
				   if($kd_prodi=='GEO'){
			              $txt.= $this->kur_GEO();
				     }else{
                       if($kd_prodi=='IF'){
			                  $txt.= $this->kur_IF();
						   }else{
						      if($kd_prodi=='IND'){
							     $txt.= $this->kur_IND();
							   }else {
                                  if($kd_prodi=='ING'){
							         $txt.= $this->kur_ING();
								  }else{
								     if($kd_prodi=='IP'){
									   $txt.= $this->kur_IP();
									 }else{ 
									   if($kd_prodi=='IPS'){
										     $txt.= $this->kur_IPS();
										   }else{
										      if($kd_prodi=='KP'){
										            $txt.= $this->kur_KP();
										         }else{
												   if($kd_prodi=='MTM'){
										                 $txt.= $this->kur_MTM();
													 }else{
                                                       if($kd_prodi=='SI'){
										                  $txt.= $this->kur_SI();
													   }else{ 	
                                                         if($kd_prodi=='TP'){
										                      $txt.= $this->kur_TP();
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
	        }
	   
       $txt.= "</fieldset>";	  
	  	   
	   return $txt;
	}
	
	function tbl_sem($prodi,$sem,$wp,$minat="",$flag_krs=1,$flag_p=0)
	{
	      $tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mtk".$sem));
		  $tbl1->addRow();
          $tbl1->addCell('Kode', null, 'header');	   
		  $tbl1->addCell('Kelompok', null, 'header');
		  $tbl1->addCell('Nama', null, 'header');
	      $tbl1->addCell('SKS', null, 'header');
          $tbl1->addCell('Syarat', null, 'header');
		  $tbl1->addCell('Praktikum', null, 'header');
		  $tbl1->addCell('Bidang Minat', null, 'header');
		  
		  if ($flag_krs==1){ 
		    $data=$this->dt_mtk->getData('prodi="'.$prodi.'" and sem='.$sem.' and wp="'.$wp.'" and flag_krs=1');
		  }else {
		    $data=$this->dt_mtk->getData('prodi="'.$prodi.'" and sem='.$sem.' and wp="'.$wp.'" and flag_krs=0 and flag_p='.$flag_p);
		  }
		  
		  $tt_sks=0;
		  if(!empty($data))
		  {
		    
			foreach($data as $row)
			{
			 $tbl1->addRow();
             $tbl1->addCell($row['kd_mk'], null, 'data');	   
		     $tbl1->addCell($row['klp_mk'], null, 'data');
		     $tbl1->addCell($row['nm_mk'], null, 'data');
	         
			 if(($prodi=='AK') or ($prodi=='IP') or ($prodi=='IF') or ($prodi=='SI') or ($prodi=='IND') or ($prodi=='GEO') or ($prodi=='IPS') or ($prodi=='ING') )
              {			 
			    $tbl1->addCell($row['sks_tot'], null, 'data');			     
			  }else{
			     if($prodi=='KP'){
				   $tbl1->addCell($row['sks_tot'].'('.$row['sks_ttm'].'-'.$row['sks_prk'].'-'.$row['sks_lpn'].')', null, 'data');
				 } 
			    else{
			     $tbl1->addCell($row['sks_tot'].'('.$row['sks_ttm'].'-'.$row['sks_prk'].')', null, 'data');
                }              
			  }
			 $tbl1->addCell($row['syarat'], null, 'data');
			 $tbl1->addCell($row['kd_lab'], null, 'data');
			 $tbl1->addCell($row['bdg_minat'], null, 'data');
			 $tt_sks+=$row['sks_tot'];
			}
		  
		  }
		  $txt1 = '';
					$txt1 = $txt1."<tr>";
						$txt1 = $txt1."<th align='right' colspan='3'>Total</th>";										
						$txt1 = $txt1."<th align='left'>".$tt_sks."</th>";
						$txt1 = $txt1."<th align='left' colspan='3'></th>";
		                $txt1 = $txt1."</tr>";
		  
		  
		  return $tbl1->display($txt1);
	
	
	}
	
	function filter_kursem($prodi,$noktp)
	{
	                $ta = 20141; 
					$nta = "Ganjil 2014";
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
					
	 $txt_sem='<select name="sem_kur" id="sem_kur">'.$txt3.'</select>';
            $txt = "";
	        $txt.= "<fieldset>";
	        $txt=$txt."<legend>Keterangan: </legend><ul>";		  
		    $txt.="<li>Filter Matakuliah berdasarkan semester </li>";
			$txt.="<li>Beri tanda centang (klick kotak putih d kolom pilih) pada mata kuliah yang anda ambil </li>";
		    $txt.="<li>Klick tombol Save untuk menyimpan data</li>";
		    $txt.="<li>Klick tombol Cetak untuk mencetak data</li>";
		    $txt.= "</ul></fieldset>";
			
			$txt.= "<fieldset>";
	        $txt=$txt."<legend>Filter: </legend>";
	        $frm = new HTML_Form();
			$txt.= "Semester ".$txt_sem.$frm->addInput('submit',"Filter","Filter",array('onclick'=>"filter_kursem('".$prodi."','".$noktp."')"));
			$txt.="</fieldset>";
	        
			$txt.="<div id = 'list_krs'>";	
            $txt.=$this->tbl_krs_mdl1($prodi,$ta,$nta,$noktp);			
	        $txt.="</div>";
	  return $txt;
	}
	
	
	function tbl_krs_mdl1($prodi,$ta,$nta,$noktp)
	{	  
		            $dt_prodi=new dt_prodi;
	                $vkd_fak = $dt_prodi->get_fak($prodi);
					  		
		  
		            $txt4= "<option value='R' selected='selected' >Reguler</option>";
					$txt4.= "<option value='N'>Non Reguler</option>";
		  
		  $tmp_input4 ='<select name="shift" id="shift">'.$txt4.'</select>'; 			
		     
		  
		  $tbl1 = new HTML_Table(null, 'display_krs', 0, 0, 0,array("id" => "lst_krs","width" => "100%"));
		  $tbl1->addRow();
          
		  $tbl1->addCell('Sem', null, 'header');
		  $tbl1->addCell('Kode', null, 'header');	   
		  $tbl1->addCell('Nama', null, 'header');
	      $tbl1->addCell('SKS', null, 'header');
          $tbl1->addCell('Pilih', null, 'header');
		  
		  $data=$this->dt_mtk->getData('prodi="'.$prodi.'" and flag_krs=1 and thn_sms='.$ta);
		  
		  $dt_krs=new dt_krs;
		  
		  $txt= "<fieldset>";
	      $txt.="<legend>Kartu Rencana Studi (KRS) Semester $nta </legend><div>";
		  $jml=0; 
		 if(!empty($data))
		  {
		    
			foreach($data as $row)
			{
			 $tbl1->addRow();
             $tbl1->addCell($row['sem'], null, 'data');
			 $tbl1->addCell($row['kd_mk'], null, 'data');	   
		     $tbl1->addCell($row['nm_mk'], null, 'data');
	         $tmp_kd=$row['NO'];
			 $tbl1->addCell($row['sks_tot'], null, 'data',array("id"=>$tmp_kd));
           	 if($dt_krs->periksa($ta,$prodi,$row['NO'],$noktp))
			 { $tmp_input = "<input type='checkbox' name='mk[]' value='$tmp_kd' id='mk' checked>";
			   $jml+=$row['sks_tot'];
			 }
			 else
			 { $tmp_input = "<input type='checkbox' name='mk[]' value='$tmp_kd' id='mk' >";}
			 
		     $tbl1->addCell($tmp_input, null, 'data',array('align'=>'center')); 			 
			}
		  
		  }
		  
		  $dt_krs->getKRS("thsmskrs='".$ta."' and b.prodi='".$prodi."' and noktphskrs='".$noktp."'");
		  
		  $tmp_input =	"<input type='text' name='totalsks' size='3' maxlength='3' id='jsks' readonly='readonly' value='$jml' style='text-align:center; color:red;'>";
		  
		  $tmp_input3 =	"<input type='text' name='kampus' size='30' maxlength='30' id='kmps' value='$dt_krs->kmps'  >";
		  
		  switch($dt_krs->kls)
		  {
		   case 'A' : $select_a="selected='selected'";
		              $select_b="";
					  $select_c="";
		              break;
		   case 'B' : $select_a="";
		              $select_b="selected='selected'";
					  $select_c="";
		              break;
           case 'C'	: $select_a="";
		              $select_b="";
					  $select_c="selected='selected'";
		              break;	   
          } 		  
		  $txt3= "<option value='A' $select_a >A</option>";
		  $txt3.= "<option value='B' $select_b >B</option>";
		  $txt3.= "<option value='C' $select_c >C</option>";
					
	      $tmp_input1 ='<select name="kls" id="kls">'.$txt3.'</select>';
		  
		  $txt.=$tbl1->display();
		  if(!empty($data))
		  {
		    $frm = new HTML_Form();
		    $txt.="</div><center><b>JUMLAH SKS YANG DIAMBIL</b>".$tmp_input."<br>";
			
			if( ($prodi=="AGT") or ($prodi=="AGB") or ($prodi=="IND") or ($prodi=="GEO") or ($prodi=="IPS") or ($prodi=="IP")) 
			{
			  $txt.="<b>KAMPUS </b>".$tmp_input3."<br>";
			}
			
			//$txt.="<b>REGULER/NON REGULER</b>".$tmp_input4."<br>";
			
			if(($prodi=="IND") or ($prodi=="ING")) 
			{
			  $txt.="<b>ANDA TERGABUNG DALAM KELAS </b>".$tmp_input1."<br>";
			}
			
			$txt.=$frm->addInput('submit',"Save","Save",array('onclick'=>"save_krs('".$vkd_fak."','".$prodi."','".$ta."','".$noktp."')",'id'=>"Save")).$frm->addInput('submit',"Cetak","Cetak",array('onclick'=>"cetak_krs('".$vkd_fak."','".$prodi."','".$ta."','".$noktp."')",'id'=>"Cetak"))."</center>";
		  }
		  $txt.="</fieldset>";	  
		  return $txt;
	 
	}
	
	function kur_AGB()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Agribisnis</li>";
	      $txt.="<li>Sumber data dari Prodi. Agribisnis via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";		    
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("AGB",$i,"w","-")."<br>";
		  }
		  $txt.="Matakuliah Pilihan <br>";		  
		  $txt.=$this->tbl_sem("AGB",0,"P","",1,0)."<br>";
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  
		  $txt.='<div id="tabs-2">';
		  	  
		  $txt.='</div>';
	  $txt.='</div>';
	 return $txt;
	}
	function kur_AGT()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Agroteknologi</li>";
	      $txt.="<li>Sumber data dari Prodi. Agroteknologi via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("AGT",$i,"w","-")."<br>";
		  }
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.='</div>';
	  $txt.='</div>';
	 return $txt;
	}   
	function kur_AK()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
          $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Akuntansi</li>";
	      $txt.="<li>Sumber data dari Prodi. Akuntansi via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
   		  for ($i=1; $i<=8; $i++)
          { 
            //$txt.="Semester ".$i."<br>";		  
		    //$txt.=$this->tbl_sem("AK",$i,"w","-")."<br>";
			
			$txt.="Matakuliah Wajib Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("AK",$i,"W","",1,0)."<br>";
			$txt.="Matakuliah Pilihan Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("AK",$i,"P","",1,0)."<br>";
						
		  }
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_GEO()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Pendidikan Geografi</li>";
	      $txt.="<li>Sumber data dari Prodi. Pendidikan Geografi via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("GEO",$i,"w","-")."<br>";
		  }
		  
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("GEO");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_IF()
	{
	 $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		 
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Teknik Informatika</li>";
	      $txt.="<li>Sumber data dari Prodi. Teknik Informatika via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		 
  		 for ($i=1; $i<=8; $i++)
          { 
            $txt.="Matakuliah Wajib Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("IF",$i,"W","-",1,0)."<br>";
			$txt.="Matakuliah Praktikum Non Krs Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("IF",$i,"W","-",0,1)."<br>";
		  }
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("IF");
		  $txt.='</div>';
	  $txt.='</div>';
	 return $txt;
	}
	function kur_IND()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Pendidikan Bahasa Indonesia</li>";
	      $txt.="<li>Sumber data dari Prodi. Pendidikan Bahasa Indonesia via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("IND",$i,"w","-")."<br>";
		  }
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("IND");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_ING()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Pendidikan Bahasa Inggris</li>";
	      $txt.="<li>Sumber data dari Prodi. Pendidikan Bahasa Inggris via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("ING",$i,"w","-")."<br>";
		  }
		 $txt.= "</fieldset>";
		 
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("ING");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_IP()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Ilmu Pemerintahan</li>";
	      $txt.="<li>Sumber data dari Prodi. Ilmu Pemerintahan via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("IP",$i,"w","-")."<br>";
		  }
		  
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("IP");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_IPS()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Pendidikan IPS</li>";
	      $txt.="<li>Sumber data dari Prodi. Pendidikan IPS via Rektorat</li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("IPS",$i,"w","-")."<br>";
		  }
		  
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("IPS");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_KP()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Perawat</li>";
	      $txt.="<li>Sumber data dari Prodi. Perawat </li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("KP",$i,"w","-")."<br>";
		  }
		  
		   $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("KP");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_MTM()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
         		 
          $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Matematika</li>";
	      $txt.="<li>Sumber data dari Prodi. Matematika </li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
				 
		 for ($i=1; $i<=8; $i++)
          { 
            $txt.="Matakuliah Wajib Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("MTM",$i,"W","",1,0)."<br>";
			$txt.="Matakuliah Pilihan Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("MTM",$i,"P","",1,0)."<br>";
			$txt.="Matakuliah Praktikum Non Krs Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("MTM",$i,"W","",0,1)."<br>";
			
		  }
		  
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("MTM");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_SI()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Sistem Informasi</li>";
	      $txt.="<li>Sumber data dari Prodi. Sistem Informasi via rektorat </li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
				 
		  
		  for ($i=1; $i<=8; $i++)
          { 
            
			$txt.="Matakuliah Wajib Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("SI",$i,"W","-",1,0)."<br>";
			$txt.="Matakuliah Praktikum Non Krs Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("SI",$i,"W","-",0,1)."<br>";
		  }
		  
		  $txt.= "</fieldset>";
		  
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.=$this->filter_kursem("SI");
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	}
	function kur_TP()
	{
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
			$txt.='<li><a href="#tabs-1">Daftar Matakuliah</a></li>';
			$txt.='<li><a href="#tabs-2">Contoh Kartu Rencana Studi (KRS) Online</a></li>';			
	  $txt.='</ul>';
		  $txt.='<div id="tabs-1">';
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Keterangan : </legend><ul>";		  
		  $txt.="<li>Dibawah ini terlampir susunan matakuliah dari Prodi. Teknologi Pangan</li>";
	      $txt.="<li>Sumber data dari Prodi. Teknologi Pangan via rektorat </li>";
		  $txt.="<li>Bentuk format penulisan susunan matakuliah merupakan interprestasi penulis program sendiri</li>";
		  $txt.="<li>Bilamana ada kekeliruan dalam penulisan ini silakan hubungi tim PSI untuk perbaikannya</li>";
		  $txt.= "</ul></fieldset>";
		  
		  $txt.= "<fieldset>";
		  $txt.="<legend>Susunan Matakuliah : </legend>";
		  
		  for ($i=1; $i<=8; $i++)
          { 
            $txt.="Semester ".$i."<br>";		  
		    $txt.=$this->tbl_sem("TP",$i,"w","-")."<br>";
		  }
		  $txt.="Matakuliah Pilihan <br>";		  
		  $txt.=$this->tbl_sem("TP",0,"P","",1,0)."<br>";
		  
		  $txt.= "</fieldset>";
		  
		  $txt.='</div>';
		  $txt.='<div id="tabs-2">';
		  $txt.='</div>';
	  $txt.='</div>';
	  return $txt;
	
	}
}
?>












