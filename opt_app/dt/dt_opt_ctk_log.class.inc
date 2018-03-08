<?php
require_once dirname(dirname(__FILE__)).'/shared.php'; 
class dt_opt_ctk_log
{
   var $tb;
   var $numrows;  
  
   function __construct(){
     $this->tb = new tb_opt_ctk_log;
	 
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
	
	function delete($nm_file,$user)
	{	
	  $this->tb->deleteRecord(array("nm_file"=>$nm_file,"userid"=>$user));
	}
	
}
?>