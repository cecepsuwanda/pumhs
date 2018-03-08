<?php
require_once 'default_table.class.inc';
class tb_kec extends Default_Table
{
    // additional class variables go here
    function tb_kec ()
    {
        $this->tablename       = 'kab_kota';
        
		$this->fieldlist       = array('id_kab_kota','kode_kab_kota','kab_kota');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['id_kab_kota'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>

