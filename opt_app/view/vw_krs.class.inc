<?php

class vw_krs
{  
    var $dt_krs;
	function __construct()	{
	  	$this->dt_krs = new dt_krs;		
	}
	
	function krs_to_pdf($prodi,$ta,$noktp)	{
	  
                    $dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_prodi='".$prodi."'");
					$vnm_prodi="";
					foreach ($data as $r){						
						  $vnm_prodi=$r['prodi'];
                          $kd_fak=$r['kd_fakultas'];						  
					}
	                
					$dt_fak=new dt_fak;
					$data = $dt_fak->getData("kd_fakultas='".$kd_fak."'");
					$vnm_fak="";
					foreach ($data as $r){						
						  $vnm_fak=$r['fakultas'];
                          						  
					}
	   
	   $tbl4 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_jdl",'cellpadding'=>'2'));
	   
	   $tbl4->addRow();		  
		 $tbl4->addCell('<font face="Times New Roman" size="10pt">'.
	                     '<b>PROGRAM STUDI '.strtoupper($vnm_prodi).'<br>'.
				             strtoupper($vnm_fak).'<br>'.
					         'UNIVERSITAS BALE BANDUNG'.
				         '</b>'.
			             '</font>',null,'data');
	   
	   $jdl = $tbl4->display().			  
			  '<br><br>'.
	          '<center>'.
			            '<font face="Times New Roman" size="10pt">'.
						       '<b>KARTU RENCANA STUDI (KRS)</b>'.
					    '</font>'.
			  '</center><br><br>';
	
      $dt_mhs = new dt_mhs; 
	  $dt_mhs->KTPada($noktp);
	 
	 
	  $txt_sem = array(1=>'Ganjil',2=>'Genap');
	  
	   $tbl2 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_mhs","width"=>"100%"));       
	   $tbl2->addRow();		  
		  $tbl2->addCell('NIM','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell($dt_mhs->nim,null,'data');
		  $tbl2->addCell('Sem. Awal','data');
          $tbl2->addCell(':',null,'data');
		  $thn = str_split($ta, 4);
		  $tbl2->addCell("",null,'data');
	   $tbl2->addRow();		  
		  $tbl2->addCell('Nama','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell($dt_mhs->Nama_mahasiswa,null,'data');
		  $tbl2->addCell('Tahun Ajaran','data');
          $tbl2->addCell(':',null,'data');
		  $thn = str_split($ta, 4);
		  $tbl2->addCell( $thn[0].'/'.($thn[0]+1),null,'data');	  
	   $tbl2->addRow();		  
		  $tbl2->addCell('Dosen Wali','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell('',null,'data');
		  $tbl2->addCell('Semester','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell( $txt_sem[$thn[1]]." ".$thn[0],null,'data');
	 
	  
	 
	  
       $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_mtk","width"=>"100%",'border'=>'1','cellpadding'=>'2'));
	   
	   $tbl->addRow(); 
	   $tbl->addCell('NO',null,'header',array('width'=>'5%'));
	   $tbl->addCell('KODE',null,'header',array('width'=>'15%'));	  
	   $tbl->addCell('NAMA',null,'header',array('width'=>'70%'));	 
	   $tbl->addCell('SKS',null,'header',array('width'=>'10%'));
	   
	  $data = $this->dt_krs->getKRS("thsmskrs='".$ta."' and b.prodi='".$prodi."' and noktphskrs='".$noktp."'");
	  
	  $jml_mtk = 1;
	  $jml_sks = 0.00;
	  if(!empty($data)){
	     
	     foreach($data as $row){
		  $tbl->addRow();
		  
		  $tbl->addCell($jml_mtk,null,'data',array('align'=>'right'));
          $tbl->addCell($row['kd_mk'],null,'data',array('align'=>'center'));
		  $tbl->addCell($row['nm_mk'],null,'data',array('align'=>'left'));
		  $tbl->addCell($row['sks_tot'],null,'data',array('align'=>'center'));
		   
		  $jml_sks+=$row['sks_tot'];  
		  $jml_mtk++;			
		 }  
	  }	
	      $tbl->addRow();		  
		  $tbl->addCell('',null,'data',array('align'=>'right','height'=>'18px'));
          $tbl->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		  $tbl->addCell('',null,'data',array('align'=>'left','height'=>'18px'));
		  $tbl->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		  
		  $tbl->addRow();
		  $tbl->addCell('Jumlah',null,'data',array('colspan'=>'3','align'=>'center'));
		  $tbl->addCell($jml_sks,null,'data',array('align'=>'center'));
		  
	   $tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_prak",'border'=>'1','width'=>'90%','cellpadding'=>'2'));
	   
	   $tbl1->addRow(); 
	   $tbl1->addCell('NO',null,'header',array('width'=>'5%'));
	   $tbl1->addCell('KODE',null,'header',array('width'=>'15%'));	  
	   $tbl1->addCell('NAMA',null,'header',array('width'=>'70%'));	 
	   

	  $data = $this->dt_krs->getKRS("thsmskrs='".$ta."' and b.prodi='".$prodi."' and noktphskrs='".$noktp."' and flag_p=1 and flag_krs=0");
      
	  $jml_mtk = 1;
	  
	  if(!empty($data)){
	     
	     foreach($data as $row){
		     
		       $tbl1->addRow();
		       $tbl1->addCell($jml_mtk,null,'data',array('align'=>'right'));
               $tbl1->addCell($row['kd_mk'],null,'data',array('align'=>'center'));
		       $tbl1->addCell($row['nm_mk'],null,'data',array('align'=>'left'));
		      $jml_mtk++;
              		  
		 }  
	  }		   
	   
	    $tbl1->addRow();
		$tbl1->addCell('',null,'data',array('align'=>'right','height'=>'18px'));
        $tbl1->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		$tbl1->addCell('',null,'data',array('align'=>'left','height'=>'18px'));
	   
	   $tbl3 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_ttd",'border'=>'1','width'=>'60%','cellpadding'=>'2'));
	   
	   $tbl3->addRow(); 
	   $tbl3->addCell('MAHASISWA',null,'header',array('width'=>'50%'));
	   $tbl3->addCell('DOSEN WALI',null,'header',array('width'=>'50%'));	  
	   $tbl3->addRow(); 
	   $tbl3->addCell(' ',null,'data',array('height'=>'50px'));
	   $tbl3->addCell(' ',null,'data',array('height'=>'50px'));
	   
	   
	   $html =
            '<html>'.
			'<style type="text/css">'.
			'table{font-family: Calibri; font-size: 9pt;}'.
			'</style>'.
			'<body>'.
			 $jdl.$tbl2->display().             
			'<br>Matakuliah : <br>'.$tbl->display();			
		
		if($kd_fak=="FMIPA" or $kd_fak=="FTI"){	
		 $html.='<br>Praktikum : <br>'.$tbl1->display();			
		}
		
		$html.='<br><br>'.$tbl3->display().
			'<br><br>'.'<font face="Calibri" size="9pt">Dicetak dari Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS) UNIBBA pada tanggal '.date("d-m-Y H:i:s").'</font>'.
            '</body>'.
			'</html>';          
		  
		  
		  $base_path = dirname(dirname(__FILE__)). '/cetak/';
		  
		  
		  $tmp = "KRS - ".$noktp.".pdf";
          
		  
		 if(file_exists($base_path.$tmp)) 
		 {
		  unlink($base_path.$tmp);		 
		 }
		  
		  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($html);
          $dompdf->set_paper('a4', 'portrait');
		  $dompdf->render();
          $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);   
		  
		  if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak/") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }
	   
	   return $base_path.$tmp;			
		
	}

	function khs_to_pdf($prodi,$ta,$noktp)	{
	  
                    $dt_prodi=new dt_prodi;
					$data = $dt_prodi->getData("kd_prodi='".$prodi."'");
					$vnm_prodi="";
					foreach ($data as $r){						
						  $vnm_prodi=$r['prodi'];
                          $kd_fak=$r['kd_fakultas'];						  
					}
	                
					$dt_fak=new dt_fak;
					$data = $dt_fak->getData("kd_fakultas='".$kd_fak."'");
					$vnm_fak="";
					foreach ($data as $r){						
						  $vnm_fak=$r['fakultas'];
                          						  
					}
	   
	   $tbl4 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_jdl",'cellpadding'=>'2'));
	   
	   $tbl4->addRow();		  
		 $tbl4->addCell('<font face="Times New Roman" size="10pt">'.
	                     '<b>PROGRAM STUDI '.strtoupper($vnm_prodi).'<br>'.
				             strtoupper($vnm_fak).'<br>'.
					         'UNIVERSITAS BALE BANDUNG'.
				         '</b>'.
			             '</font>',null,'data');
	   
	   $jdl = $tbl4->display().			  
			  '<br><br>'.
	          '<center>'.
			            '<font face="Times New Roman" size="10pt">'.
						       '<b>KARTU HASIL STUDI (KHS)</b>'.
					    '</font>'.
			  '</center><br><br>';
	
      $dt_mhs = new dt_mhs; 
	  $dt_mhs->KTPada($noktp);
	 
	 
	  $txt_sem = array(1=>'Ganjil',2=>'Genap');
	  
	   $tbl2 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_mhs","width"=>"100%"));       
	   $tbl2->addRow();		  
		  $tbl2->addCell('NIM','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell($dt_mhs->nim,null,'data');
		  $tbl2->addCell('Sem. Awal','data');
          $tbl2->addCell(':',null,'data');
		  $thn = str_split($ta, 4);
		  $tbl2->addCell("",null,'data');
	   $tbl2->addRow();		  
		  $tbl2->addCell('Nama','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell($dt_mhs->Nama_mahasiswa,null,'data');
		  $tbl2->addCell('Tahun Ajaran','data');
          $tbl2->addCell(':',null,'data');
		  $thn = str_split($ta, 4);
		  $tbl2->addCell( $thn[0].'/'.($thn[0]+1),null,'data');	  
	   $tbl2->addRow();		  
		  $tbl2->addCell('Dosen Wali','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell('',null,'data');
		  $tbl2->addCell('Semester','data');
          $tbl2->addCell(':',null,'data');
		  $tbl2->addCell( $txt_sem[$thn[1]]." ".$thn[0],null,'data');
	 
	  
	 
	  
       $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_mtk","width"=>"100%",'border'=>'1','cellpadding'=>'2'));
	   
	   $tbl->addRow(); 
	   $tbl->addCell('NO',null,'header',array('width'=>'5%'));
	   $tbl->addCell('KODE',null,'header',array('width'=>'15%'));	  
	   $tbl->addCell('NAMA',null,'header',array('width'=>'40%'));	 
	   $tbl->addCell('SKS',null,'header',array('width'=>'10%'));
	   $tbl->addCell('HM',null,'header',array('width'=>'10%'));
	   $tbl->addCell('AM',null,'header',array('width'=>'10%'));
	   $tbl->addCell('SKSXAM',null,'header',array('width'=>'10%'));
	   
	  $data = $this->dt_krs->getKRS("thsmskrs='".$ta."' and b.prodi='".$prodi."' and noktphskrs='".$noktp."'");
	  
	  $jml_mtk = 1;
	  $jml_sks = 0.00;
	  $sksam = 0;
	  $jml_sksam = 0;
	  if(!empty($data)){
	     
	     foreach($data as $row){
		  $tbl->addRow();
		  
		  $tbl->addCell($jml_mtk,null,'data',array('align'=>'right'));
          $tbl->addCell($row['kd_mk'],null,'data',array('align'=>'center'));
		  $tbl->addCell($row['nm_mk'],null,'data',array('align'=>'left'));
		  $tbl->addCell($row['sks_tot'],null,'data',array('align'=>'center'));
		  $tbl->addCell(is_null($row['nilaikrs']) ? 0 :$row['nilaikrs'],null,'data',array('align'=>'center'));
		  $tbl->addCell($row['bobotkrs'],null,'data',array('align'=>'center'));
          $sksam = $row['sks_tot']*$row['bobotkrs'];
		  $tbl->addCell($sksam,null,'data',array('align'=>'center'));
		  
		  $jml_sksam+=$sksam; 
		  $jml_sks+=$row['sks_tot'];  
		  $jml_mtk++;			
		 }  
	  }	
	      $tbl->addRow();		  
		  $tbl->addCell('',null,'data',array('align'=>'right','height'=>'18px'));
          $tbl->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		  $tbl->addCell('',null,'data',array('align'=>'left','height'=>'18px'));
		  $tbl->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		  $tbl->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		  $tbl->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		  $tbl->addCell('',null,'data',array('align'=>'center','height'=>'18px'));

		  $tbl->addRow();
		  $tbl->addCell('Jumlah',null,'data',array('colspan'=>'3','align'=>'center'));
		  $tbl->addCell($jml_sks,null,'data',array('align'=>'center'));
		  $tbl->addCell('',null,'data',array('align'=>'center'));
		  $tbl->addCell('',null,'data',array('align'=>'center'));
		  $tbl->addCell($jml_sksam,null,'data',array('align'=>'center'));
		  $tbl->addRow();
		  $tbl->addCell('IP',null,'data',array('colspan'=>'3','align'=>'center'));
		  $tbl->addCell( $jml_sks == 0 ? '0.00' : number_format($jml_sksam/$jml_sks,2,',','.'),null,'data',array('colspan'=>'4','align'=>'center'));
		  
		  
	   $tbl1 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_prak",'border'=>'1','width'=>'90%','cellpadding'=>'2'));
	   
	   $tbl1->addRow(); 
	   $tbl1->addCell('NO',null,'header',array('width'=>'5%'));
	   $tbl1->addCell('KODE',null,'header',array('width'=>'15%'));	  
	   $tbl1->addCell('NAMA',null,'header',array('width'=>'60%'));
	   $tbl1->addCell('HM',null,'header',array('width'=>'10%'));	 
	   

	  $data = $this->dt_krs->getKRS("thsmskrs='".$ta."' and b.prodi='".$prodi."' and noktphskrs='".$noktp."' and flag_p=1 and flag_krs=0");
      
	  $jml_mtk = 1;
	  
	  if(!empty($data)){
	     
	     foreach($data as $row){
		     
		       $tbl1->addRow();
		       $tbl1->addCell($jml_mtk,null,'data',array('align'=>'right'));
               $tbl1->addCell($row['kd_mk'],null,'data',array('align'=>'center'));
		       $tbl1->addCell($row['nm_mk'],null,'data',array('align'=>'left'));
		       $tbl1->addCell($row['nilaikrs'],null,'data',array('align'=>'center'));
		      $jml_mtk++;
              		  
		 }  
	  }		   
	   
	    $tbl1->addRow();
		$tbl1->addCell('',null,'data',array('align'=>'right','height'=>'18px'));
        $tbl1->addCell('',null,'data',array('align'=>'center','height'=>'18px'));
		$tbl1->addCell('',null,'data',array('align'=>'left','height'=>'18px'));
		$tbl1->addCell('',null,'data',array('align'=>'left','height'=>'18px'));
	   
	   $tbl3 = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "tb_ttd",'border'=>'1','width'=>'60%','cellpadding'=>'2'));
	   
	   $tbl3->addRow(); 
	   $tbl3->addCell('MAHASISWA',null,'header',array('width'=>'50%'));
	   $tbl3->addCell('DOSEN WALI',null,'header',array('width'=>'50%'));	  
	   $tbl3->addRow(); 
	   $tbl3->addCell(' ',null,'data',array('height'=>'50px'));
	   $tbl3->addCell(' ',null,'data',array('height'=>'50px'));
	   
	   
	   $html =
            '<html>'.
			'<style type="text/css">'.
			'table{font-family: Calibri; font-size: 9pt;}'.
			'</style>'.
			'<body>'.
			 $jdl.$tbl2->display().             
			'<br>Matakuliah : <br>'.$tbl->display();			
		
		if($kd_fak=="FMIPA" or $kd_fak=="FTI"){	
		 $html.='<br>Praktikum : <br>'.$tbl1->display();			
		}
		
		$html.='<br><br>'.$tbl3->display().
			'<br><br>'.'<font face="Calibri" size="9pt">Dicetak dari Sistem Informasi Pendataan Ulang Mahasiswa (PUMHS) UNIBBA pada tanggal '.date("d-m-Y H:i:s").'</font>'.
            '</body>'.
			'</html>';          
		  
		  
		  $base_path = dirname(dirname(__FILE__)). '/cetak/';
		  
		  
		  $tmp = "KHS - ".$noktp.".pdf";
          
		  
		 if(file_exists($base_path.$tmp)) 
		 {
		  unlink($base_path.$tmp);		 
		 }
		  
		  
		  $dompdf = new DOMPDF();
          $dompdf->load_html($html);
          $dompdf->set_paper('a4', 'portrait');
		  $dompdf->render();
          $output = $dompdf->output();
          file_put_contents($base_path.$tmp, $output);   
		  
		  if($base_path=="/home/uni10000/public_html/pumhs/opt_app/cetak/") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/cetak/";
	      }else
          {
		    $base_path="cetak/";
		  }
	   
	   return $base_path.$tmp;			
		
	}
	
	function list_mhs(){
	
	   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs7","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('Fak. - Prodi', null, 'header');
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('NIM', null, 'header');
        $tbl->addCell('Jml SKS', null, 'header');
       		
      	
		
		$data = $this->dt_krs->getMHS("flag_krs=1"); 
		
		if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  
		  
			$i=$i+1;
			$tbl->addRow();        
		    $tbl->addCell($i, null, 'data');
		    $tbl->addCell($row['fak'].'-'.$row['prodi'], null, 'data');
		    $tbl->addCell(strtoupper($row['nama_mahasiswa']), null, 'data');
		    $tbl->addCell($row['NIM'], null, 'data');
		    $tbl->addCell($row['jml_sks'], null, 'data');	
            		
			
		}
		  
		 
      }
	 
	 return $tbl->display("");
	
	}
	function list_mtk(){
	
	   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_mhs8","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('Fak. - Prodi', null, 'header');
		$tbl->addCell('Semester', null, 'header');
		$tbl->addCell('Kode', null, 'header');
	    $tbl->addCell('Nama', null, 'header');
        $tbl->addCell('Jml mhs', null, 'header');		
      			
		$data = $this->dt_krs->getMTK(""); 
		
		if(!empty($data))
      {	 
		$i=0;
		foreach($data as $row)
		{
		  
		  
			$i=$i+1;
			$tbl->addRow();        
		    $tbl->addCell($i, null, 'data');
		    $tbl->addCell($row['fak'].'-'.$row['prodi'], null, 'data');
		    $tbl->addCell($row['semkrs'], null, 'data');
		    $tbl->addCell($row['kd_mk'], null, 'data');
			$tbl->addCell($row['nm_mk'], null, 'data');
		    $tbl->addCell($row['jml_mhs'], null, 'data');		    
			
		}
		  
		 
      }
	 
	 return $tbl->display("");
	
	}
	
    function list_nilai($prodi,$sem,$kode,$shift,$kelas,$fak){
	
	   $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => "lst_nilai","width"=>"100%"));
		
		$tbl->addRow();
        $tbl->addCell('No.', null, 'header');	    
		$tbl->addCell('Nama', null, 'header');
	    $tbl->addCell('NIM', null, 'header');
	    $tbl->addCell('A', null, 'header');
	    $tbl->addCell('B', null, 'header');
	    $tbl->addCell('C', null, 'header');
	    $tbl->addCell('D', null, 'header');
	    $tbl->addCell('E', null, 'header');
	    $tbl->addCell('T', null, 'header');
        	
		$data = $this->dt_krs->getMHS1("prodi='$prodi' and thsmskrs='$sem' and nokmkkrs='$kode' and shiftkrs='$shift' and kelaskrs='$kelas'"); 
		
		if(!empty($data))
      {	 
		$i=0;
		$nilai = array('A','B','C','D','E','T');
		foreach($data as $row)
		{	    
		    $i=$i+1;
			$tbl->addRow();        
		    $tbl->addCell($i, null, 'data');
		    $tbl->addCell(strtoupper($row['Nama_mahasiswa']), null, 'data');
		    $tbl->addCell($row['NIM'], null, 'data');
		    $idx_name = $row['noktphskrs'];
		    foreach ($nilai as $value) {
		      $Kchek = $row['nilaikrs']==$value	? 'checked':''; 
		      $txt_checkbox = "<input type='radio' name='nilai[$idx_name]' value='$value' $Kchek>";  
		      $tbl->addCell($txt_checkbox, null, 'data');	
		    }           		
			
		}
		  
		 
      }
	 $frm = new HTML_Form();
	 $txt=$frm->addInput('submit',"Save","Save",array('onclick'=>"save_nilai('".$kode."','".$shift."','".$kelas."','".$fak."')",'id'=>"Save"));
	 return $tbl->display("").$txt;
	
	}
	
}
?>