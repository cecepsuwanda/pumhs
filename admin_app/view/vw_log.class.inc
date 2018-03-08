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
 
 


require_once $base_path."dt/dt_opt_log.class.inc";
require_once $base_path."dt/dt_ctk_log.class.inc";
require_once $base_path."dt/dt_admin_log.class.inc";
require_once $base_path."dt/dt_mhs.class.inc";


include_once "../basic_class/html_table.class.php";


class vw_log
{   var $dtoptlog;
    var $dtadminlog;
	var $dtmhslog;
	var $dtctklog;
	
	function vw_log()
	{
	  	$this->dtoptlog = new dt_opt_log;
        $this->dtadminlog = new dt_admin_log;
		$this->dtmhslog = new dt_mhs;
        $this->dtctklog = new dt_ctk_log;		
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
      
	  
	  $txt.= "<fieldset>";
	  $txt=$txt."<legend>SQL Log Error :</legend>";
	  $file = '../sql_log.txt';
	  $current = file_get_contents($file);
	  $txt=$txt.'<textarea name="alamat" id="alamat" style="width:750px;height:300px;">'.$current.'</textarea>';
	  $txt.= "</fieldset>";
	  
      return $txt;	  
	}	
	
	function ctk_log()
	{
	  $txt = "<fieldset>";
	  $txt=$txt."<legend>Log Cetak : </legend>";
	  
	    $tbl = new HTML_Table(null, 'display', 0, 0, 0,array("id" => 'logctk',"width"=>"100%"));
		$tbl->addRow();
        $tbl->addCell('No', null, 'header');
		$tbl->addCell('Nama File', null, 'header');
	    $tbl->addCell('Tgl Cetak', null, 'header');	   
		$tbl->addCell('User', null, 'header');
		
		
		$data = $this->dtctklog->getData("");
		
		$i=1;
		if(!empty($data))
        {	
		  foreach($data as $row)
		 {
		  $tbl->addRow();        
		  $tbl->addCell($i, null, 'data');
		  
		  $server = $_SERVER['DOCUMENT_ROOT'];
		  if($server=="/home/uni10000/public_html/pumhs") {
            $base_path="http://pumhs.unibba.ac.id/admin_app/";
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
	      $tbl->addCell($row['userid'], null, 'data');
		  $i+=1;
		 } 
	    }
		
		
	  
	  $txt.= "<button onclick='cetak_statistik(1)'>Cetak Statistik to Pdf</button>"."<button onclick='cetak_statistik(2)'>Cetak Statistik to Excel</button>".$tbl->display(""). "</fieldset>";      
	  
      return $txt;	
	}
}
?>












