(*
Name        : hw1.ml
Author      : Jack Harrington
Date        : February 9, 2022
Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
Description : Homework 1 for cs496
*)

type program = int list
let square : program = [0;2;2;3;3;4;4;5;5;1]
let letter_e : program = [0;2;2;3;3;5;5;4;3;5;4;3;3;5;5;1]

(* Mirror Functions *)
let mirror_help x =
  match x with
  | 2 -> 4
  | 4 -> 2
  | 3 -> 5
  | 5 -> 3
  | _ -> x

let mirror_image x = List.map mirror_help x

(* Rotate Function *)
let rotate x =
  match x with
  | 2 -> 3
  | 3 -> 4
  | 4 -> 5
  | 5 -> 2
  | _ -> x

let rotate_90_letter x = List.map rotate x
let rotate_90_word x = List.map rotate_90_letter x

(* Repeat Function *)
let rec repeat n e =
  match n with
  | 0 -> []
  | m -> e :: repeat (n-1) e

(* Append Function *)
let rec appendl x =
  match x with
  | [] -> []
  | h::t -> h @ appendl t

(* Pantograph Function *)
let rec pantograph_nm x p =
  match x with
  | 0 -> []
  | _ -> 
    (match p with
     | [] -> []
     | h::t -> 
      (match h with
       | 0 | 1 -> h :: (pantograph_nm x t)
       | _ -> (repeat x h) @ (pantograph_nm x t)))

let pantograph_f x p =
  List.rev (List.fold_left
    (fun r h -> 
      (match h with
       | 0 | 1 -> h::r
       | _ -> (repeat x h) @ r)) [] p)

(* Coverage Function *)
let rec coverage_helper c p =
  match p with
  | [] -> []
  | h::t -> (match h with
      | 2 -> (fst c, (snd c) + 1) :: coverage_helper (fst c, (snd c) + 1) t
      | 3 -> ((fst c) + 1, snd c) :: coverage_helper ((fst c) + 1, snd c) t
      | 4 -> (fst c, (snd c) - 1) :: coverage_helper (fst c, (snd c) - 1) t
      | 5 -> ((fst c) - 1, snd c) :: coverage_helper ((fst c) - 1, snd c) t
      | _ -> c :: coverage_helper c t)
      
let rec coverage c a = c :: coverage_helper c a

(* Compress Function *)
let rec compress_helper p x =
  match p with
  | [] -> []
  | h1::[] -> (h1, x) :: []
  | h1:: h2 :: t ->
    if h1 != h2
    then (h1, x) :: (compress_helper (h2 :: t) 1)
    else compress_helper (h2 ::t) (x + 1)

let compress p = compress_helper p 1

(* Uncompress Function *)
let rec uncompress x =
  match x with
  | [] -> []
  | (src, tgt)::t -> (repeat tgt src) @ (uncompress t)

let rec uncompess_m x = List.flatten (List.map (fun (src, tgt) -> repeat tgt src) x)
let rec uncompress_f x = List.rev (List.fold_left ((fun r h -> (repeat (snd h)(fst h)) @ r)) [] x)

(* Optimize Function *)
let rec optimize_helper x pen =
  match x with
  | [] -> []
  | h::t -> (match pen, h with
      | true, 1 -> optimize_helper t true
      | true, 0 -> h :: optimize_helper t false
      | false, 1 -> h :: optimize_helper t true
      | false, 0 -> optimize_helper t false
      | _,_ -> h :: (optimize_helper t pen))

let optimize p = optimize_helper p true