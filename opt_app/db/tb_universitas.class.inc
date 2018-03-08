<?php
require_once 'default_table.class.inc';
class tb_universitas extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'tmst_universitas';
        
		$this->fieldlist       = array('Kode_Univ','Nama_Univ');
        
		$this->sql_orderby         = 'Kode_Univ,Nama_Univ';
		
		$this->fieldlist['Kode_Univ'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>