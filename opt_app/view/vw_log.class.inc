<?php

class vw_log
{   var $dtoptlog;
    var $dtadminlog;
	var $dtmhslog;
	var $dtctklog;
	var $dtopt;
	
	function __construct()
	{
	  	$this->dtoptlog = new dt_opt_log;
        $this->dtadminlog = new dt_admin_log;
		$this->dtmhslog = new dt_mhs;
        $this->dtctklog = new dt_opt_ctk_log;
        $this->dtopt = new dt_operator;		
	}
	
	function lst_log()
	{
	  $txt = "<fieldset>";
	  $txt=$txt."<legend>Log Mahasiswa : </legend>";
	  
	    $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => 'logmhs',"width"=>"100%"));
		$tbl->addRow();
        $tbl->addCell('No', null, 'header');
		$tbl->addCell('Tanggal Login', null, 'header');
	    $tbl->addCell('KTP', null, 'header');	   
		$tbl->addCell('Nama', null, 'header');
	    
		$sql="Tgl_Log is not null";	
		
		$data = $this->dtmhslog->getDataEntri($sql);
		
		$i=1;
		if(!empty($data))
        {	
		  foreach($data as $row)
		 {
		  $tbl->addRow();        
		  $tbl->addCell($i, null, 'data');
		  $tbl->addCell($row['Tgl_Log'], null, 'data');
		  $tbl->addCell($row['NO_KTP'], null, 'data');
	      $tbl->addCell($row['Nama_mahasiswa'], null, 'data');
		  $i+=1;
		 } 
	    }
		
		
	  
	  $txt.= $tbl->display(""). "</fieldset>";
	  
	  $txt.= "<fieldset>";
	  $txt=$txt."<legend>Log Operator :</legend>";
	    
		$tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => 'logopt',"width"=>"100%"));
		$tbl->addRow();
        $tbl->addCell('No', null, 'header');
		$tbl->addCell('Tanggal Login', null, 'header');
	    $tbl->addCell('Tanggal Logout', null, 'header');	   
		$tbl->addCell('User', null, 'header');
	    
			
		
		$data = $this->dtoptlog->getData("");
		
		$i=1;
		if(!empty($data))
        {	
		  foreach($data as $row)
		 {
		  $tbl->addRow();        
		  $tbl->addCell($i, null, 'data');
		  $tbl->addCell($row['lg_time'], null, 'data');
		  $tbl->addCell($row['out_time'], null, 'data');
	      $tbl->addCell($row['nama_user'], null, 'data');
		  $i+=1;
		 } 
	    }
		
		
	  
	  $txt.= $tbl->display(""). "</fieldset>";  
	  
	  
	  $txt.= "<fieldset>";
	  $txt=$txt."<legend>Log Admin :</legend>";
	  
	  $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => 'logadmin',"width"=>"100%"));
		$tbl->addRow();
        $tbl->addCell('No', null, 'header');
		$tbl->addCell('Tanggal Login', null, 'header');
	    $tbl->addCell('Tanggal Logout', null, 'header');	   
		$tbl->addCell('User', null, 'header');
	    
			
		
		$data = $this->dtadminlog->getData("");
		
		$i=1;
		if(!empty($data))
        {	
		  foreach($data as $row)
		 {
		  $tbl->addRow();        
		  $tbl->addCell($i, null, 'data');
		  $tbl->addCell($row['lg_time'], null, 'data');
		  $tbl->addCell($row['out_time'], null, 'data');
	      $tbl->addCell($row['user'], null, 'data');
		  $i+=1;
		 } 
	    }
		
		
	  
	  $txt.= $tbl->display(""). "</fieldset>";
      
	  
      return $txt;	  
	}	
	
	function tbl_ctk_log($opt_id,$sql_str,$nm_class,$id_nm)
	{
	    $tbl = new HTML_Table(null, $nm_class, 0, 0, 0,array("id" => $id_nm,"width"=>"100%"));
		$tbl->addRow();
        $tbl->addCell('No', null, 'header');
		$tbl->addCell('Nama File', null, 'header');
	    $tbl->addCell('Tgl Cetak', null, 'header');	   
		$tbl->addCell('User', null, 'header');
		$tbl->addCell('Aksi', null, 'header');
		
		
		$data = $this->dtctklog->getData($sql_str);
		
		$i=1;
		if(!empty($data))
        {	
		  foreach($data as $row)
		 {
		  $tbl->addRow();        
		  $tbl->addCell($i, null, 'data');
		  
		  $server = $_SERVER['DOCUMENT_ROOT'];
		  if($server=="/home/uni10000/public_html/pumhs") {
            $base_path="http://pumhs.unibba.ac.id/opt_app/";
	      }else
          {
		    $base_path="";
		  }    
		  
		  $link=$base_path."cetak/".$row['nm_file'];
		  $link1="cetak/".$row['nm_file'];
		  if(file_exists($link1)){
		    $tbl->addCell("<a href='".$link."'>".$row['nm_file']."</a>", null, 'data');
		  }else
		  {
		    $tbl->addCell($row['nm_file'], null, 'data');
		  }
		  
		  
		  $tbl->addCell($row['tgl_ctk'], null, 'data');
		  
		  $data1 = $this->dtopt->getData("id_opt='".$opt_id."'");
		  if(!empty($data1))
          {	
			foreach($data1 as $row1)
			  {
			   $opt_name = $row1['nama_user']; 
		   	  } 			
		  }else
		  {
		    $opt_name ="";
		  }
	      $tbl->addCell($opt_name, null, 'data');
		  
		  if(file_exists($link1)){
		    $link='javascript:deletefile("'.$link1.'")';
			$tbl->addCell("<a href='".$link."'>"."Delete"."</a>", null, 'data');
		  }else
		  {
		    $tbl->addCell("Delete", null, 'data');
		  }
		  $i+=1;
		 } 
	    }
	    return $tbl->display("");
	}
	
	function ctk_log($kd_fak,$opt_id)
	{
	  	          		
	  $txt='<div id="tabs">';
	  $txt.='<ul>';
	  $txt.='<li><a href="#tabs-1">Hasil Validasi</a></li>';
	  $txt.='<li><a href="#tabs-2">Form Verifikasi</a></li>';
	  $txt.='<li><a href="#tabs-3">Hasil Verifikasi</a></li>';
	  $txt.='<li><a href="#tabs-4">Absen Perwalian</a></li>';
      $txt.='<li><a href="#tabs-5">DHMD</a></li>';
	  
	  $txt.='</ul>';
			
      $tmp='"'.$kd_fak.'"';
	  $txt.='<div id="tabs-1">';
	  $txt.="<div>".$this->tbl_ctk_log($opt_id,"userid='".$opt_id."' and (nm_file like 'Data PUMHS%' or nm_file like 'Data Blm Lyk%')","display_ctklog","log_ctk1")."</div>";
	  $txt.='</div>';	  
	  
	  $txt.='<div id="tabs-2">';  
	  $txt.="<div>".$this->tbl_ctk_log($opt_id,"userid='".$opt_id."' and nm_file like 'Form Verifikasi%'","display_ctklog","log_ctk2")."</div>";
	  $txt.='</div>';    
	  
	  $txt.='<div id="tabs-3">';	  
	  $txt.="<div>".$this->tbl_ctk_log($opt_id,"userid='".$opt_id."' and nm_file like 'Data Hasil Verifikasi%'","display_ctklog","log_ctk1")."</div>";
	  $txt.='</div>';
	  
	  $txt.='<div id="tabs-4">';	  
	  $txt.="<div>".$this->tbl_ctk_log($opt_id,"userid='".$opt_id."' and nm_file like 'Absen Perwalian%'","display_ctklog","log_ctk1")."</div>";
	  $txt.='</div>';
	  
	  $txt.='<div id="tabs-5">';	  
	  $txt.="<div>".$this->tbl_ctk_log($opt_id,"userid='".$opt_id."' and nm_file like 'DHMD%'","display_ctklog","log_ctk1")."</div>";
	  $txt.='</div>';
	  
	  $txt.='</div>';
	  
      return $txt;	
	}
}
?>












