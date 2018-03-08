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
 
 include_once $base_path.'db/tb_ctk_log.class.inc';
 

class dt_ctk_log
{
   var $tb;
   var $numrows;  
  
   function dt_ctk_log(){
     $this->tb = new tb_ctk_log;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	

	function insert($nm_file,$user)
	{
	
	$this->tb->insertRecord(array("nm_file"=>$nm_file,"tgl_ctk"=>date("Y-m-d H:i:s"),"userid"=>$user));
	}
	
}
?>