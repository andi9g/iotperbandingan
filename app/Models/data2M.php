<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class data2M extends Model
{
    use HasFactory;
    protected $table = "data2";
    protected $primaryKey = "iddata";
    protected $guarded = [];
}
